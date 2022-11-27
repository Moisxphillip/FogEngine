#ifndef FOG_RESOURCES
#define FOG_RESOURCES

#include "../lib/IncludeAll.hpp"

class Resources
{
    private:
        std::unordered_map<std::string, SDL_Texture*> _ImageTable;
        std::unordered_map<std::string, Mix_Music*> _MusicTable;
        std::unordered_map<std::string, Mix_Chunk*> _SoundTable;

    public:
        SDL_Texture* GetImage(std::string);
        Mix_Music* GetMusic(std::string);
        Mix_Chunk* GetSound(std::string);

        void ClearImages();
        void ClearMusics();
        void ClearSounds();
    
};


#endif//FOG_RESOURCES