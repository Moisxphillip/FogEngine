#ifndef FOG_SPRITE
#define FOG_SPRITE

#define SDL_BASE
#define SDL_IMAGE
#include "../lib/IncludeSDL.hpp"
#include <string>

class Sprite
{
    private:
        SDL_Texture* _Sprite_Texture;
        int _SpriteWidth;
        int _SpriteHeight;
        SDL_Rect _ClipRect;

    public:
        Sprite();
        Sprite(std::string);
        ~Sprite();
        void Open(std::string);
        void SetClip(int, int, int, int);
        void Render(int, int);
        int GetWidth();
        int GetHeight();
        bool IsOpen();
};

#endif//FOG_SPRITE