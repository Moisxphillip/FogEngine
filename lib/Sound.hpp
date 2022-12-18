#ifndef FOG_SOUND
#define FOG_SOUND

#include "../lib/IncludeAll.hpp"

class Sound : public Component
{
    private:    
        Mix_Chunk* _SoundChunk;
        int _SoundChannel;
        int _SoundVolume;
        void _SoundPosition();
    
    public:    
        bool Pan;
        Sound(GameObject&);
        Sound(GameObject&, std::string);
        ~Sound();

        void Play(int);
        void Stop();
        void Volume(int);
        void Open(std::string);
        bool IsOpen();
        bool IsPlaying();
        
        //Inheritance Functions
        bool Is(std::string);
        void Render();
        void Start();
        void Update(float);

};

#endif//FOG_SOUND