#ifndef FOG_SPRITE
#define FOG_SPRITE

#include <string>

#define SDL_BASE
#define SDL_IMAGE
#include "../lib/IncludeSDL.hpp"
#include "../lib/Tools.hpp"
#include "../lib/Component.hpp"

class Sprite : public Component
{
    private:
        SDL_Texture* _SpriteTexture;
        int _SpriteWidth;
        int _SpriteHeight;
        SDL_Rect _ClipRect;

    public:
        Sprite(GameObject&);
        Sprite(GameObject&, std::string);
        ~Sprite();
        
        void Open(std::string);
        void SetClip(int, int, int, int);
        void Render();
        int GetWidth();
        int GetHeight();
        bool IsOpen();

        void Update(float);
        bool Is(std::string);
        
};

#endif//FOG_SPRITE