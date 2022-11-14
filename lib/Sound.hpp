#ifndef FOG_SOUND
#define FOG_SOUND

#include "../lib/Component.hpp"

#define SDL_MIXER
#include "../lib/IncludeSDL.hpp"

class Sound : public Component
{
    private:    
        Mix_Chunk* _SoundChunk;
        int _SoundChannel;
        int _SoundVolume;
    
    public:    
        Sound(GameObject&);
        Sound(GameObject&, std::string);
        ~Sound();

        void Play(int);
        void Stop();
        void Open(std::string);
        bool IsOpen();
        
        //Inheritance Functions
        void Update(float);
        void Render();
        bool Is(std::string);

};

#endif//FOG_SOUND