#ifndef FOG_MUSIC
#define FOG_MUSIC

#define SDL_BASE
#define SDL_MIXER
#include "../lib/IncludeSDL.hpp"
#include "../lib/Tools.hpp"

class Music
{
    private:
        Mix_Music* _Music;

    public:
        Music();
        Music(std::string);
        ~Music();
        void Play(int);
        void Stop(int);
        void Open(std::string);
        bool IsOpen();

};

#endif//FOG_MUSIC