#ifndef FOG_SPRITEGL
#define FOG_SPRITEGL

#include "../lib/IncludeAll.hpp"

class SpriteGL : public Component
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
        GLuint _VboID;

    public:
        bool Loop;
        Timer ToSelfDestruct;
        float LifeTime;

        SpriteGL(GameObject&);
        SpriteGL(GameObject&, std::string);
        SpriteGL(GameObject&, std::string, int, float);
        SpriteGL(GameObject&, std::string, int, float, float);
        ~SpriteGL();
        
        void Open(std::string);
        void SetClip(int, int, int, int);
        void Init(float, float, float, float);
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

#endif// FOG_SPRITEGL