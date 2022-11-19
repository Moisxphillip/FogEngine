#include "../lib/IncludeAll.hpp"


State::State()
{
    _QuitRequested = false;
    _StateMusic = nullptr;
    //_StateBg = nullptr;
	    
	//Init random machine
    Rng.seed(5);
	Rng.range(0,1000);

    LoadAssets();
    _StateMusic->Play(-1, 1000);
}

State::~State()
{
    delete _StateMusic;
    _StateMusic = nullptr;
    //delete _StateBg;
    //_StateBg = nullptr;
    GameObjVec.clear();
}

bool State::QuitRequested()
{
    return _QuitRequested;
}

void State::LoadAssets()
{
    _StateMusic = new Music(FMUS_STAGE1);
	GameObject *BgElement = new GameObject;
    Sprite* StateBg = new Sprite(*BgElement, FIMG_OCEAN);//TODO fix
	
	BgElement->AddComponent(StateBg);
	BgElement->Box = Rect(0,0,StateBg->GetWidth(),StateBg->GetHeight());
	GameObjVec.emplace_back(BgElement);
//	unique_ptr<GameObject>(BgElement);

}

void State::Update(float Dt)
{
    _Input();
	
	for(int i = 0; i< GameObjVec.size(); i++)
	{
		GameObjVec[i]->Update(Dt);
	}

	for(int i = 0; i< GameObjVec.size(); i++)
	{
		if(GameObjVec[i]->IsDead())
		{
			GameObjVec.erase(GameObjVec.begin()+i);
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
		if(event.type == SDL_QUIT) 
        {
			_QuitRequested = true;
		}
		
		// Se o evento for clique...
		if(event.type == SDL_MOUSEBUTTONDOWN) 
        {
			// Percorrer de trás pra frente pra sempre clicar no objeto mais de cima
			for(int i = GameObjVec.size() - 1; i >= 0; --i) 
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
			if(event.key.keysym.sym == SDLK_ESCAPE) 
            {
				_QuitRequested = true;
			}
			// Se não, crie um objeto
			else 
            {
                Vec2 NewRot(200, 0);
				std::cout << NewRot << "\n";
				std::cout << Rng.gen() << "\n";

                NewRot.Rotate(-M_PI + M_PI*(Rng.gen()/500.0));
				std::cout << NewRot << "\n";
				
				Vec2 Pos(mouseX,mouseY);
				NewRot= NewRot + Pos;
				std::cout << NewRot << "\n";
				_AddObject((int)NewRot.x, (int)NewRot.y);
			}
		}
	}
}

void State::_AddObject(int x, int y)
{
	GameObject *Enemy = new GameObject;
	Sprite *EnemySprite = new Sprite(*Enemy, FIMG_PENGFACE);
	Enemy->Box = Rect(x,y,EnemySprite->GetWidth(),EnemySprite->GetHeight());
	Sound *Sfx = new Sound(*Enemy, FAUD_BOOM);
	Face *FaceEnemy = new Face(*Enemy);
	Enemy->AddComponent(EnemySprite);
	Enemy->AddComponent(Sfx);
	Enemy->AddComponent(FaceEnemy);
	GameObjVec.emplace_back(Enemy);
	
}

void State::Render()
{
	for(int i = 0; i< GameObjVec.size(); i++)
	{
		GameObjVec[i]->Render();
	}
}