#include "../lib/IncludeAll.hpp"


ScreenFilter::ScreenFilter(GameObject& GameObj, Color FilterColor)
: Component(GameObj)
{
    this->FilterColor = FilterColor;
    _FilterSurface = nullptr;
    _FilterSurface = SDL_CreateRGBSurface(0,FOG_SCRWIDTH, FOG_SCRHEIGHT, 32, 0,0,0,0);
}

ScreenFilter::~ScreenFilter()
{
    if(_FilterSurface != nullptr)
    {
        SDL_FreeSurface(_FilterSurface);
        _FilterSurface = nullptr;
    }
}

bool ScreenFilter::Is(std::string Type)
{
    return ("ScreenFilter" == Type);
}

void ScreenFilter::Render()
{
    SDL_Texture* ToShow = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), _FilterSurface);
    SDL_SetTextureBlendMode(ToShow, SDL_BLENDMODE_BLEND);
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), ToShow, nullptr, nullptr);
	SDL_DestroyTexture(ToShow);
}

void ScreenFilter::Update(float Dt)
{
    SDL_SetSurfaceAlphaMod(_FilterSurface, 255-FilterColor.A);
    SDL_FillRect(_FilterSurface, nullptr, FilterColor.ColorUint32());
}
		
		
		
