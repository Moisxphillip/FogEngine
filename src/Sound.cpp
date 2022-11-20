#include "../lib/IncludeAll.hpp"

Sound::Sound(GameObject& GameObj)
: Component(GameObj)
{
    Pan = false;
    _SoundChunk = nullptr;
    _SoundVolume = 50;
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


void Sound::Play(int Times = 0)
{
    for(int i = 0; i<FOG_SOUNDCHANNELS; i++)
    {
        if(Mix_Playing(i) == 0)//Found a free channel
        {
            if(Pan)
            {
                //Set volume for each channel based on the gameobject center position
                Vec2 SoundPos = GameObjAssoc.Box.Center();
                int R = 127 + ((int)SoundPos.x >> 3); //FIXME Will need a better calculation when adding screen resize options
                R=(R>255?255:R);//Overflow prevention
                int L = 383-R;
                L=(L>255?255:L);//Overflow prevention
                
                Mix_SetPanning(i, L, R);
            }
            else
            {
                Mix_Volume(i, _SoundVolume);
            }
            _SoundChannel = Mix_PlayChannel(i, _SoundChunk, Times);
            return;
        }
    }
    Error("Sound::Play: Mix_PlayChannel could not find an empty channel");
}

void Sound::Stop()
{
    if(_SoundChunk != nullptr)
    {
        Mix_HaltChannel(_SoundChannel);
    }
}

void Sound::Volume(int NewVolume)
{
    _SoundVolume = NewVolume;
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

bool Sound::IsPlaying()
{
    return (Mix_Playing(_SoundChannel) != 0);
}

//Position-based sound pan&volume control
void Sound::_SoundPosition()
{

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
