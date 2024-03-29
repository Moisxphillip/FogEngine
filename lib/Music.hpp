#ifndef FOG_MUSIC
#define FOG_MUSIC

#include "../lib/IncludeAll.hpp"

class Music
{
    private:        
        Mix_Music* _Music;
        int _MusicVolume;

    public:
        Music();
        Music(std::string);
        ~Music();
        
        void Play(int, int);
        void Stop(int);
        void Open(std::string);
        bool IsOpen();

};

#endif//FOG_MUSIC