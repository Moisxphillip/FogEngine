#include "../lib/IncludeAll.hpp"

State::State()
{
    _QuitRequested = false; //Allows loop until quit is requested
    _StateMusic = nullptr; 
    _QuitFade = false;
	_Started = false;
	_FaceEnabled = false;//Disables face input
	//Init random machine
    Rng.seed(5);
	Rng.range(0,1000);
}

State::~State()
{
    delete _StateMusic;
    _StateMusic = nullptr;

    GameObjVec.clear(); //Gets rid of objects made
    LateRenderVec.clear(); //Gets rid of objects made
}

void State::Start()
{
	LoadAssets();
	for(int i = 0; i< (int)(GameObjVec.size()); i++)
    {
        GameObjVec[i]->Start();
    }
    _Started = true;
}

std::weak_ptr<GameObject> State::AddGameObj(GameObject* NewGameObject)
{
	std::shared_ptr<GameObject> NewSharedObj(NewGameObject);

	GameObjVec.push_back(NewSharedObj);//Stores GameObject on scene GameObj vector
	if(_Started)
	{
        GameObjVec[GameObjVec.size()-1]->Start(); //Make it start if it's added during state run
    }
	std::weak_ptr<GameObject> NewWeakObj(NewSharedObj) ;
	return NewWeakObj;
}

std::weak_ptr<GameObject> State::AddLateRenderObj(GameObject* NewGameObject)
{
	std::shared_ptr<GameObject> NewSharedObj(NewGameObject);

	LateRenderVec.push_back(NewSharedObj);//Stores new pointer on Late Render vector
	if(_Started)
	{
        GameObjVec[GameObjVec.size()-1]->Start(); //Make it start if it's added during state run
    }
	std::weak_ptr<GameObject> NewWeakObj(NewSharedObj) ;
	return NewWeakObj;
}

std::weak_ptr<GameObject> State::GetGameObjPtr(GameObject* ComparePtr)
{
    for(int i = 0; i< (int)(GameObjVec.size()); i++)
	{
		if(GameObjVec[i].get() == ComparePtr)
		{
			return GameObjVec[i];
		}
	}
	return {};
}

bool State::QuitRequested()
{
    return _QuitRequested; //Program will leave the Game::Run() Loop  if true
}

void State::LoadAssets()
{
	//Basic state elements
    GameObject *BgElement = new GameObject;//Create a gameobject to be associated with the background sprite 
    Sprite* StateBg = new Sprite(*BgElement, FIMG_OCEAN);//Load image background
	CameraFollower *FixedBg = new CameraFollower(*BgElement);
	BgElement->AddComponent(FixedBg); //Keeps initial coordinates fixed on camera
	BgElement->AddComponent(StateBg); //registers component on the gameObject
	BgElement->Box = Rect(0,0,StateBg->GetWidth(),StateBg->GetHeight());//Sets dimensions for the background GameObject
	AddGameObj(BgElement);//Stores GameObject on scene GameObj vector

	//Init TileMap
	GameObject* StateMap = new GameObject();
	TileSet* StateTileSet = new TileSet(FOG_TILEWIDTH, FOG_TILEHEIGHT, FIMG_TILESET);
	TileMap* StateTileMap = new TileMap(*StateMap, FMAP_TILEMAP, StateTileSet);
	StateMap->AddComponent(StateTileMap);
	AddGameObj(StateMap);
	AddLateRenderObj(StateMap);

	//Penguin
	GameObject* PenguinObj = new GameObject();
	PenguinBody* Penguin = new PenguinBody(*PenguinObj);
	PenguinObj->Box.SetCenter(Vec2(100,100));
	PenguinObj->AddComponent(Penguin);
	AddGameObj(PenguinObj);
	Cam.Follow(PenguinObj);
	
	//Alien
	GameObject* AlienObj = new GameObject();
	Alien* Et = new Alien(*AlienObj, FOG_NUMMINIONS);
	AlienObj->Box.SetCenter(Vec2(512,300));
	AlienObj->AddComponent(Et);
	AddGameObj(AlienObj);

	//Play music
	_StateMusic = new Music(FMUS_STAGE1);//Load the music file for the current state
	_StateMusic->Play(-1, 1000); //Start playing phase theme
}

void State::Update(float Dt)
{
	//Sets QuitFade flag if Esc or close button were pressed
	if(!_QuitFade && (InputManager::GetInstance().IsKeyDown(K_ESC) 
		|| InputManager::GetInstance().QuitRequested())) 
	{
		_StateMusic->Stop(1000);
		_QuitFade = true;
		_FadeOut();
	}

	if(_QuitFade && !Mix_PlayingMusic())//Ensures fadeout finishes before closing
	{
		_QuitRequested = true;
	}

	Cam.Update(Dt);
		
	for(int i = 0; i< (int)GameObjVec.size()-1; i++)
	{
		Component* ColA = GameObjVec[i]->GetComponent("Collider");
		if(ColA != nullptr)
		{
			for(int j = i+1; j < (int)GameObjVec.size(); j++)
			{
				Component* ColB = GameObjVec[j]->GetComponent("Collider");
				if(ColB != nullptr)
				{
					if(Collision::IsColliding(GameObjVec[i]->Box, GameObjVec[j]->Box, GameObjVec[i]->Angle, GameObjVec[j]->Angle))
					{
						GameObjVec[i]->Collided(*GameObjVec[j]);
						GameObjVec[j]->Collided(*GameObjVec[i]);
					}
				}
			}
		}
	}
	//Calls updates for contained objects and remove dead objects
	GameObjUpdate(Dt);
}

void State::GameObjUpdate(float Dt)
{
	//Game Object Updates
	for(int i = 0; i< (int)(GameObjVec.size()); i++)
	{
		GameObjVec[i]->Update(Dt);//Updates based on input and Dt
	}
	
	for(int i = 0; i< (int)(GameObjVec.size()); i++)
	{
		if(GameObjVec[i]->IsDead())
		{
			GameObjVec.erase(GameObjVec.begin()+i); //Removes stuff discarded by RequestDelete()
			i--;
		}
	}

	//Late Render Updates
	for(int i = 0; i< (int)(LateRenderVec.size()); i++)
	{
		LateRenderVec[i]->Update(Dt); //Calls render procedure for the late stuff
	}

	for(int i = 0; i< (int)(LateRenderVec.size()); i++)
	{
		if(LateRenderVec[i]->IsDead())
		{
			LateRenderVec.erase(LateRenderVec.begin()+i); //Removes stuff discarded by RequestDelete()
			i--;
		}
	}
}

void State::_FadeOut()
{
	//create object for holding the fadeout and a generic gameobject
	GameObject* FadeOutGO = new GameObject();
	Generic* FadeOut = new Generic(*FadeOutGO, "FadeOut");

	//Set start function
	FadeOut->SetStart(
	[](Generic* FadeOut)
	{
		FadeOut->Float["Time"] = 0;
		FadeOut->Int["Counter"] = 0;
	});

	//Set update function
	FadeOut->SetUpdate(
	[](float Dt, Generic* FadeOut)
	{
		FadeOut->Float["Time"]+=Dt;
		FadeOut->Int["Counter"]+=12;
		(FadeOut->Int["Counter"] >= 255 ? FadeOut->Int["Counter"] = 255 : FadeOut->Int["Counter"]);

		if(FadeOut->Float["Time"] >= 5)
		{
			FadeOut->RequestDelete();
		}
	});

	//Set render function
	FadeOut->SetRender(
	[](Generic* FadeOut)
	{
		SDL_Surface* SurfScreen = SDL_CreateRGBSurface(0,FOG_SCRWIDTH, FOG_SCRHEIGHT, 32, 0,0,0,0);
		SDL_SetSurfaceAlphaMod(SurfScreen,FadeOut->Int["Counter"]);
		SDL_FillRect(SurfScreen, nullptr, 0x00000000);
		SDL_Texture* ToShow = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), SurfScreen);
		SDL_SetTextureBlendMode(ToShow, SDL_BLENDMODE_BLEND);
		SDL_RenderCopy(Game::GetInstance().GetRenderer(), ToShow, nullptr, nullptr);
		SDL_DestroyTexture(ToShow);
		SDL_FreeSurface(SurfScreen);
	});

	FadeOutGO->AddComponent(FadeOut);
	AddLateRenderObj(FadeOutGO);
}

void State::Render()
{
	for(int i = 0; i< (int)(GameObjVec.size()); i++)
	{
		GameObjVec[i]->Render(); //Calls render procedure for each existing GameObject
	}
	
	for(int i = 0; i< (int)(LateRenderVec.size()); i++)
	{
		LateRenderVec[i]->Render(); //Calls render procedure for the late stuff
	}
}