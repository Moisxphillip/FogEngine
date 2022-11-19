#ifndef FOG_SOUND
#define FOG_SOUND

#include "../lib/IncludeAll.hpp"

class Sound : public Component
{
    private:    
        Mix_Chunk* _SoundChunk;
        int _SoundChannel;
        int _SoundVolume;
        bool _SoundPan;
        void _SoundPosition();
    
    public:    
        Sound(GameObject&);
        Sound(GameObject&, std::string);
        ~Sound();

        void Play(int);
        void Stop();
        void Volume(int);
        void Open(std::string);
        bool IsOpen();
        bool IsPlaying();

        void PanOn();
        void PanOff();
        
        //Inheritance Functions
        void Update(float);
        void Render();
        bool Is(std::string);

};

#endif//FOG_SOUND