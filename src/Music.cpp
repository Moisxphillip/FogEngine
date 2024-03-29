#include "../lib/IncludeAll.hpp"

Music::Music()
{
    _Music = nullptr;
}

Music::Music(std::string File)
{
    _Music = nullptr;
    Open(File);
}

Music::~Music()
{
}


//-1 = infinite loop
void Music::Play(int Times = -1, int FadeIn = 0)
{
    if(_Music == nullptr)
    {
        Error("Music::Play: Music asset not loaded");
        return;
    }

    if(Mix_FadeInMusic(_Music, Times, FadeIn))
    {
        Error("Music::Play: Music device failed to fade in and play");
    }
}

void Music::Stop(int FadeOut = 1500)
{
    if(!Mix_FadeOutMusic(FadeOut))
    {
        Error("Music::Stop: Fadeout Could not be scheduled");
    }
}

void Music::Open(std::string File)
{
    _Music = Resources::GetMusic(File);
    if(_Music == nullptr)
    {
        Error("Music::Open: Music asset could not be loaded");
    }
}

bool Music::IsOpen()
{
    return (_Music != nullptr);
}
