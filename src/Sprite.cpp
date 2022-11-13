#include "../lib/Sprite.hpp"

//Including on the hpp results in failure, so...
#include "../lib/Game.hpp"

Sprite::Sprite()
{
    _SpriteTexture = nullptr;
}

Sprite::Sprite(std::string File)
{
    _SpriteTexture = nullptr;
    Open(File);
}

Sprite::~Sprite()
{
    if(_SpriteTexture != nullptr)
    {
        SDL_DestroyTexture(_SpriteTexture);
    }
    _SpriteTexture = nullptr;
}

void Sprite::Open(std::string File)
{
    _SpriteTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), File.c_str());
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

void Sprite::Render(int x, int y)
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
