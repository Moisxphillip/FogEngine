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
        Vec2 _Scale;
        int _FrameCount;
        int _CurrFrame;
        float _TimeElapsed;
        float _FrameTime;
        Flip _Orientation;

    public:
        bool Loop;
        Timer ToSelfDestruct;
        float LifeTime;

        Sprite(GameObject&);
        Sprite(GameObject&, std::string);
        Sprite(GameObject&, std::string, int, float);
        Sprite(GameObject&, std::string, int, float, float);
        ~Sprite();
        
        void Open(std::string);
        void SetClip(int, int, int, int);
        int GetWidth();
        int GetHeight();
        void SetScale(float, float);
        Vec2 GetScale();
        bool IsOpen();

        void SetFrame(int);
        void SetFrameCount(int);
        void SetFrameTime(float);
        void SetFlip(Flip);
        Flip GetFlip();
        
        bool Is(std::string);
        void Render();
        void Render(float, float);
        void Render(float, float, float);
        void Start();
        void Update(float);
        
};

#endif//FOG_SPRITE