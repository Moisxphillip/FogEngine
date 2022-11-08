#ifndef FOG_SPRITE
#define FOG_SPRITE

#include <string>

#define SDL_BASE
#define SDL_IMAGE
#include "../lib/IncludeSDL.hpp"
#include "../lib/Tools.hpp"

class Sprite
{
    private:
        SDL_Texture* _SpriteTexture;
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