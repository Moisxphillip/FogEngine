#ifndef FOG_SCRFADE
#define FOG_SCRFADE

#include "../lib/IncludeAll.hpp"

class ScreenFade : public Component
{
    private:
        //SDL_Surface* _FilterSurface;
        ScreenFilter _FadeFilter;
        bool _FadeIn;
        bool _Finished;
        float _StartPercent;
        float _FinishPercent;
        float _CurrPercent;
        float _Step;
        float _Time;

    public:
        Color FilterColor;
        Timer FadeStep;

        ScreenFade(GameObject&, Color, float, float, float);
        ~ScreenFade();
        void RedirectFade(float);
        void SetTime(float);
        
        bool Is(std::string);
        void Render();
        void Update(float);

};

#endif// FOG_SCRFADE