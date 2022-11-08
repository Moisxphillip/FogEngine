#include "../lib/State.hpp"

State::State()
{
    _QuitRequested = false;
    _StateMusic.Open("./res/audio/stageState.ogg");
    _StateMusic.Play(-1);
}

bool State::QuitRequested()
{
    return _QuitRequested;
}

void State::LoadAssets()
{
    //preload state assets to prevent future problems
}

void State::Update(float Dt)
{
    if(SDL_QuitRequested())
    {
        _QuitRequested = true;
    }
}

void State::Render()
{

}