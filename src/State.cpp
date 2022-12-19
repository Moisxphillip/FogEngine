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
	GameObject *StateMap = new GameObject();
	TileSet *StateTileSet = new TileSet(FOG_TILEWIDTH, FOG_TILEHEIGHT, FIMG_TILESET);
	TileMap *StateTileMap = new TileMap(*StateMap, FMAP_TILEMAP, StateTileSet);
	StateMap->AddComponent(StateTileMap);
	AddGameObj(StateMap);

	//Alien
	GameObject *AlienObj = new GameObject();
	Alien *Et = new Alien(*AlienObj, 4);
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
	}

	if(_QuitFade && !Mix_PlayingMusic())//Ensures fadeout finishes before closing
	{
		_QuitRequested = true;
	}

	//Cam following object
	if(InputManager::GetInstance().KeyPress(SDLK_t))
	{
		if(!Cam.IsFollowing())
		{
			Cam.Follow(GameObjVec[2].get()); 
		}
		else
		{
			Cam.Unfollow();
		}
	}

	Cam.Update(Dt);

	if(InputManager::GetInstance().KeyPress(K_P))
	{
		_FaceEnabled = !_FaceEnabled; //Enables the old face input
	}
	else if(_FaceEnabled && InputManager::GetInstance().KeyPress(K_SPACE)) 
	{
		Vec2 NewRot(200, 0);
		NewRot.Rotate(-M_PI + M_PI*(Rng.gen()/314.15));
		Vec2 Pos(InputManager::GetInstance().GetMouseX(),
			InputManager::GetInstance().GetMouseY());
		NewRot = NewRot + Pos; //Rotate object
		_AddObject((int)NewRot.x, (int)NewRot.y);
	}
	else if(_FaceEnabled && InputManager::GetInstance().MousePress(M_LEFT)) 
	{
		// Percorrer de trás pra frente pra sempre clicar no objeto mais de cima
		for(int i = (int)(GameObjVec.size()) - 1; i >= 0; --i) 
		{
			if(GameObjVec[i]->Box.Contains(Vec2(float(InputManager::GetInstance().GetMouseX()),
				float(InputManager::GetInstance().GetMouseY())))) 
			{
				Face* face = (Face*)GameObjVec[i]->GetComponent("Face");
				
				if ( nullptr != face ) 
				{
					// Aplica dano
					face->Damage(int(Rng.gen()) % 10 + 10);
					break;
				}
			}
		}
	}
	//End of input

	//Calls updates for contained objects and remove dead objects
	GameObjUpdate(Dt);
}

void State::GameObjUpdate(float Dt)
{
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
}

void State::_AddObject(int x, int y)
{
	GameObject *Enemy = new GameObject; //Create a base object for holding the components
	Sprite *EnemySprite = new Sprite(*Enemy, FIMG_PENGFACE);//Create a Sprite
	Enemy->Box = Rect(x-(EnemySprite->GetWidth()>>1),y-(EnemySprite->GetHeight()>>1),
	        		EnemySprite->GetWidth(),EnemySprite->GetHeight());//Sets Sprite dimensions
	Sound *Sfx = new Sound(*Enemy, FAUD_BOOM); //Create a Sound for the object
	Face *FaceEnemy = new Face(*Enemy);//Define a Face for controlling received damage
	Sfx->Pan = true;
    
	//Insert components on the new GameObject
	Enemy->AddComponent(EnemySprite);
	Enemy->AddComponent(Sfx);
	Enemy->AddComponent(FaceEnemy);

	AddGameObj(Enemy); //Register GameObject on the GameObjVec for executing with other objects in the scene
}

void State::Render()
{
	TileMap* OuterLayer = nullptr;//For keeping outer layer when there's parallax with layers over the reference
	for(int i = 0; i< (int)(GameObjVec.size()); i++)
	{
		if(OuterLayer == nullptr)
		{
			OuterLayer = (TileMap*)(GameObjVec[i]->GetComponent("TileMap"));
		}
		GameObjVec[i]->Render(); //Calls render procedure for each existing GameObject
	}

	if(OuterLayer != nullptr)
	{
		OuterLayer->Render();//Prints outer layer for real parallax
	}
}