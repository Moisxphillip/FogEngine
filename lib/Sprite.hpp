#ifndef FOG_SPRITE
#define FOG_SPRITE

#include "../lib/IncludeAll.hpp"

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
        int GetWidth();
        int GetHeight();
        bool IsOpen();
        
        bool Is(std::string);
        void Render();
        void Render(float, float);
        void Render(float, float, float, SDL_RendererFlip&);
        void Render(float, SDL_RendererFlip&);
        void Start();
        void Update(float);
        
        
};

#endif//FOG_SPRITE