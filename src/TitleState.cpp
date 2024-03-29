#include "../lib/IncludeAll.hpp"

TitleState::TitleState()
{
    _QuitRequested = false; //Allows loop until quit is requested
	_PopRequested = false;
	_Started = false;
}

TitleState::~TitleState()
{

}


void TitleState::LoadAssets()
{
    GameObject* Title = new GameObject();
    Sprite* TitleImage = new Sprite(*Title, FIMG_MAINSCR);
    Title->Box.Redimension(Vec2(TitleImage->GetWidth(),TitleImage->GetHeight()));
    Title->AddComponent(TitleImage);
    AddGameObj(Title);
    Cam.Follow(Title);

    GameObject* TitleDesc = new GameObject();
    Text* TitleText = new Text(*TitleDesc, FTTF_CALL, 30, Text::SOLID, "Press SPACE to start!", TextColor.ColorSDL());
    TitleDesc->Box.SetCenter(Title->Box.Center());
    TitleDesc->Box.y += 200;    
    TitleDesc->AddComponent(TitleText);
    AddGameObj(TitleDesc);
}

void TitleState::Update(float Dt)
{
    TextColorChange.Update(Dt);
    if(TextColorChange.Get() > 4)
    {
        TextColorChange.Restart();
    }

    //Rainbow effect
    float ColorMod = TextColorChange.Get()*90;
    TextColor.SetHSV(ColorMod, 100, 80);
    for(int i = 0; i< (int) (GameObjVec.size()); i++)
    {
        Text *ScrTxt = (Text*)GameObjVec[i]->GetComponent("Text");
        if(ScrTxt != nullptr)
        {
            ScrTxt->SetColor(TextColor.ColorSDL());
            break;
        }
    } 

    if(InputManager::GetInstance().KeyPress(K_SPACE))
    {
        StageState* Play = new StageState;
        Game::GetInstance().Push(Play);
    }
    if((InputManager::GetInstance().IsKeyDown(K_ESC) || InputManager::GetInstance().QuitRequested())) 
	{
		_PopRequested = true;
		_QuitRequested = true;
    }
    _UpdateArray(Dt);
}

void TitleState::Render()
{
    _RenderArray();
}


void TitleState::Start()
{
    LoadAssets();
    _StartArray();
}

void TitleState::Pause()
{

}

void TitleState::Resume()
{

}
