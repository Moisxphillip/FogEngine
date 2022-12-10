#include "../lib/IncludeAll.hpp"


State::State()
{
    _QuitRequested = false; //Allows loop until quit is requested
    _StateMusic = nullptr; 
    _QuitFade = false;
	//Init random machine
    Rng.seed(5);
	Rng.range(0,1000);
    LoadAssets();
    _StateMusic->Play(-1, 1000); //Start playing phase theme
}

State::~State()
{
    delete _StateMusic;
    _StateMusic = nullptr;

    GameObjVec.clear(); //Gets rid of objects made
}

bool State::QuitRequested()
{
    return _QuitRequested; //Program will leave the Game::Run() Loop  if true
}

void State::LoadAssets()
{
    _StateMusic = new Music(FMUS_STAGE1);//Load the music file for the current state
	GameObject *BgElement = new GameObject;//Create a gameobject to be associated with the background sprite 
    Sprite* StateBg = new Sprite(*BgElement, FIMG_OCEAN);//Load image background
	CameraFollower *FixedBg = new CameraFollower(*BgElement);
	BgElement->AddComponent(FixedBg); //Keeps initial coordinates fixed on camera
	BgElement->AddComponent(StateBg); //registers component on the gameObject
	BgElement->Box = Rect(0,0,StateBg->GetWidth(),StateBg->GetHeight());//Sets dimensions for the background GameObject
	
	GameObjVec.emplace_back(BgElement);//Stores GameObject on scene GameObj vector
		
	//Init TileMap
	GameObject *StateMap = new GameObject();
	TileSet *StateTileSet = new TileSet(FOG_TILEWIDTH, FOG_TILEHEIGHT, FIMG_TILESET);
	TileMap *StateTileMap = new TileMap(*StateMap, FMAP_TILEMAP, StateTileSet);
	StateMap->AddComponent(StateTileMap);
	GameObjVec.emplace_back(StateMap);
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

	Cam.Update(Dt);

	if(InputManager::GetInstance().KeyPress(K_SPACE)) 
	{
		Vec2 NewRot(200, 0);
		NewRot.Rotate(-M_PI + M_PI*(Rng.gen()/500.0));
		Vec2 Pos(InputManager::GetInstance().GetMouseX(),
			InputManager::GetInstance().GetMouseY());
		NewRot = NewRot + Pos; //Rotate object
		_AddObject((int)NewRot.x, (int)NewRot.y);
	}
	else if(InputManager::GetInstance().MousePress(M_LEFT)) 
	{
		// Percorrer de trás pra frente pra sempre clicar no objeto mais de cima
		for(int i = (int)(GameObjVec.size()) - 1; i >= 0; --i) 
		{
			// Obtem o ponteiro e casta pra Face.
			GameObject* go = (GameObject*) GameObjVec[i].get();
			// Nota: Desencapsular o ponteiro é algo que devemos evitar ao máximo.
			// O propósito do unique_ptr é manter apenas uma cópia daquele ponteiro,
			// ao usar get(), violamos esse princípio e estamos menos seguros.
			// Esse código, assim como a classe Face, é provisório. Futuramente, para
			// chamar funções de GameObjects, use objectArray[i]->função() direto.

			if(go->Box.Contains(Vec2(float(InputManager::GetInstance().GetMouseX()),
				float(InputManager::GetInstance().GetMouseY())))) 
			{
				Face* face = (Face*)go->GetComponent("Face");
				
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

	GameObjVec.emplace_back(Enemy); //Register GameObject on the GameObjVec for executing with other objects in the scene
}

void State::Render()
{
	for(int i = 0; i< (int)(GameObjVec.size()); i++)
	{
		if(i == 0)
		{
			GameObjVec[0]->Box.x = 0;
			GameObjVec[0]->Box.y = 0;
		}
		else
		{
			GameObjVec[i]->Box -= Cam.Position + Cam.Speed;
		}

		GameObjVec[i]->Render(); //Calls render procedure for each existing GameObject
	}
}