#ifndef FOG_SCRFILTER
#define FOG_SCRFILTER

#include "../lib/IncludeAll.hpp"

class ScreenFilter : public Component
{
    private:
        SDL_Surface* _FilterSurface;

    public:
        Color FilterColor;
        ScreenFilter(GameObject&, Color);
        ~ScreenFilter();

        bool Is(std::string);
        void Render();
        void Update(float);

};

#endif// FOG_SCRFILTER