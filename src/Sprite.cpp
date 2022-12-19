#include "../lib/IncludeAll.hpp"

Sprite::Sprite(GameObject& GameObj)
: Component(GameObj)
{
    _SpriteTexture = nullptr;
    _Scale = Vec2(1,1);
}

Sprite::Sprite(GameObject& GameObj, std::string File)
: Sprite(GameObj)
{
    Open(File);
}

Sprite::~Sprite()
{
}

void Sprite::Open(std::string File)
{
    _SpriteTexture = Resources::GetImage(File);
    if(_SpriteTexture == nullptr)
    {
        Error("Sprite::Open: Image could not be loaded");
    }

    if(SDL_QueryTexture(_SpriteTexture, nullptr, nullptr, &_SpriteWidth, &_SpriteHeight))
    {
        Error("Sprite::Open: QueryTexture failed");
    }
    SetClip(0,0, _SpriteWidth, _SpriteHeight);
}

void Sprite::SetClip(int x, int y, int w, int h)
{
    _ClipRect.x = x;
    _ClipRect.y = y;
    _ClipRect.w = w;
    _ClipRect.h = h;
}


int Sprite::GetWidth()
{
    return (_SpriteWidth * _Scale.x);
}

int Sprite::GetHeight()
{
    return (_SpriteHeight * _Scale.y);
}

void Sprite::SetScale(float ScaleX, float ScaleY)
{
    _Scale = Vec2(ScaleX, ScaleY);
}

Vec2 Sprite::GetScale()
{
    return _Scale;
}

bool Sprite::IsOpen()
{
    return (_SpriteTexture != nullptr);
}

//Inheritance
bool Sprite::Is(std::string Type)
{
    return ("Sprite" == Type);
}

void Sprite::Render()
{
    Render(GameObjAssoc.Box.x, GameObjAssoc.Box.y);
}

void Sprite::Render(float x, float y)
{
    Render(x, y, GameObjAssoc.Angle);
}

void Sprite::Render(float x, float y, float Angle)
{
    SDL_Rect DestinyRect;
    DestinyRect.x = x - Game::GetInstance().GetState().Cam.Position.x;
    DestinyRect.y = y - Game::GetInstance().GetState().Cam.Position.y;
    DestinyRect.w = _ClipRect.w  * _Scale.x;
    DestinyRect.h = _ClipRect.h * _Scale.y;


    // SDL_Rect DestinyRect;
    // DestinyRect.x = x;
    // DestinyRect.y = y;
    // DestinyRect.w = _ClipRect.w;
    // DestinyRect.h = _ClipRect.h;
    if(SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), _SpriteTexture, &_ClipRect, &DestinyRect, Vec2::RadToDeg(Angle), nullptr, SDL_FLIP_NONE))
    {
        Error("Sprite::Render: Sprite copy to render device has failed");
    }
}

void Sprite::Start()
{
}

void Sprite::Update(float Dt)
{
}


