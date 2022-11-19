#include "../lib/IncludeAll.hpp"

Sound::Sound(GameObject& GameObj)
: Component(GameObj)
{
    _SoundPan = false;  
    _SoundChunk = nullptr;
}

Sound::Sound(GameObject& GameObj, std::string File)
: Sound(GameObj)
{
    Open(File);
}

Sound::~Sound()
{
    Stop();
    Mix_FreeChunk(_SoundChunk);
}


void Sound::Play(int Times = 1)
{
    _SoundChannel = Mix_PlayChannel(-1, _SoundChunk, Times);
    if(_SoundChannel == -1)
    {
        Error("Sound::Play: Mix_PlayChannel could not find an empty channel");
    }
}

void Sound::Stop()
{
    if(_SoundChunk != nullptr)
    {
        Mix_HaltChannel(_SoundChannel);
    }
}

void Sound::Open(std::string File)
{
    _SoundChunk = Mix_LoadWAV(File.c_str());
    if(_SoundChunk == nullptr)
    {
        Error("Sound::Load: Mix_LoadWAV could not load the soundchunk "+File);
    }
}

bool Sound::IsOpen()
{
    return (_SoundChunk != nullptr);
}

//Position-based sound pan&volume control
void Sound::_SoundPosition()
{

}

inline void Sound::PanOn()
{
    _SoundPan = true;
}

inline void Sound::PanOff()
{
    _SoundPan = false;
}

//Inheritance Functions
void Sound::Update(float Dt)
{

}

void Sound::Render()
{

}

bool Sound::Is(std::string Type)
{
    return Type == "Sound";
}
