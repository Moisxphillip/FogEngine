#include "../lib/Music.hpp"

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
    Mix_FreeMusic(_Music);
    _Music = nullptr;
}


//-1 = infinite loop
void Music::Play(int Times = -1)
{
    if(_Music == nullptr)
    {
        Error("Music asset not loaded");
    }

    if(Mix_PlayMusic(_Music, Times))
    {
        Error("Music device failed");
    }
}

void Music::Stop(int FadeOut = 1500)
{
    if(!Mix_FadeOutMusic(FadeOut))
    {
        Error("Fadeout Could not be scheduled");
    }
}

void Music::Open(std::string Path)
{
    _Music = Mix_LoadMUS(Path.c_str());
    if(_Music == nullptr)
    {
        Error("Music asset could not be loaded");
    }
}

bool Music::IsOpen()
{
    return (_Music != nullptr);
}
