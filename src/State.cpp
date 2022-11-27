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
    _Input(); //Calls Input management
	
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

void State::_Input() 
{
	SDL_Event event;
	int mouseX, mouseY;	

	// Obtenha as coordenadas do mouse
	SDL_GetMouseState(&mouseX, &mouseY);

	// SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
	while (SDL_PollEvent(&event)) 
    {
		// Se o evento for quit, setar a flag para terminação
		if(event.type == SDL_QUIT && !_QuitFade) 
        {
			_StateMusic->Stop(1000);
            _QuitFade = true;
		}
		
		// Se o evento for clique...
		if(event.type == SDL_MOUSEBUTTONDOWN) 
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

				if(go->Box.Contains(Vec2(float(mouseX), float(mouseY)))) 
                {
					Face* face = (Face*)go->GetComponent("Face");
					
					if ( nullptr != face ) 
                    {
						// Aplica dano
						face->Damage(int(Rng.gen()) % 10 + 10);
						// Sai do loop (só queremos acertar um)
						break;
					}
				}
			}
		}
		if(event.type == SDL_KEYDOWN) {
			// Se a tecla for ESC, setar a flag de quit
			if(event.key.keysym.sym == SDLK_ESCAPE && !_QuitFade) 
            {
                _StateMusic->Stop(1000);
                _QuitFade = true;
			}
			// Se não, crie um objeto
			else 
            {
                Vec2 NewRot(200, 0);
                NewRot.Rotate(-M_PI + M_PI*(Rng.gen()/500.0));
				Vec2 Pos(mouseX,mouseY);
				NewRot = NewRot + Pos; //Rotate object
				_AddObject((int)NewRot.x, (int)NewRot.y);
			}
		}

        if(!Mix_PlayingMusic())//Ensures fadeout finishes before closing
        {
            _QuitRequested = true;
        }

		return;
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
		GameObjVec[i]->Render(); //Calls render procedure for each existing GameObject
	}
}