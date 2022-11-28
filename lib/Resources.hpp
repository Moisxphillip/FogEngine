#ifndef FOG_RESOURCES
#define FOG_RESOURCES

#include "../lib/IncludeAll.hpp"

class Resources
{
    private:
        static std::unordered_map<std::string, SDL_Texture*> _ImageTable;
        static std::unordered_map<std::string, Mix_Music*> _MusicTable;
        static std::unordered_map<std::string, Mix_Chunk*> _SoundTable;

    public:
        static SDL_Texture* GetImage(std::string&);
        static Mix_Music* GetMusic(std::string&);
        static Mix_Chunk* GetSound(std::string&);

        static void ClearImages();
        static void ClearMusics();
        static void ClearSounds();
        static void FlushContext();
    
};

#endif//FOG_RESOURCES