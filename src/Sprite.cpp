#include "../lib/IncludeAll.hpp"


Sprite::Sprite(GameObject& GameObj)
: Component(GameObj)
{
    _SpriteTexture = nullptr;
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

void Sprite::Render()
{
    Render(GameObjAssoc.Box.x, GameObjAssoc.Box.y);
    
}

void Sprite::Render(float x, float y)
{
    SDL_Rect DestinyRect;
    DestinyRect.x = x;
    DestinyRect.y = y;
    DestinyRect.w = _ClipRect.w;
    DestinyRect.h = _ClipRect.h;
    if(SDL_RenderCopy(Game::GetInstance().GetRenderer(), _SpriteTexture, &_ClipRect, &DestinyRect))
    {
        Error("Sprite::Render: Sprite copy to render device has failed");
    }
}

int Sprite::GetWidth()
{
    return _SpriteWidth;
}

int Sprite::GetHeight()
{
    return _SpriteHeight;
}

bool Sprite::IsOpen()
{
    return (_SpriteTexture != nullptr);
}

void Sprite::Update(float Dt)
{
}

bool Sprite::Is(std::string Type)
{
    return ("Sprite" == Type);
}
