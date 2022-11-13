#include "../lib/State.hpp"

State::State()
{
    _QuitRequested = false;
    _StateMusic = nullptr;
    _StateBg = nullptr;

    LoadAssets();
    _StateMusic->Play(-1, 1000);
    
}

State::~State()
{
    delete _StateMusic;
    _StateMusic = nullptr;
    delete _StateBg;
    _StateBg = nullptr;
}

bool State::QuitRequested()
{
    return _QuitRequested;
}

void State::LoadAssets()
{
    _StateMusic = new Music(FMUS_STAGE1);
    _StateBg = new Sprite(FIMG_OCEAN);
}

void State::Update(float Dt)
{
    if(SDL_QuitRequested())
    {
        _StateMusic->Stop(1000);
        _QuitRequested = true;
    }
}

void State::Render()
{
    _StateBg->Render(0,0);
}