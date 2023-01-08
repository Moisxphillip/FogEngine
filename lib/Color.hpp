#ifndef FOG_COLOR
#define FOG_COLOR

#include "../lib/IncludeAll.hpp"


class Color
{
    private:

    public:
    uint8_t R;
    uint8_t G;
    uint8_t B;
    uint8_t A;
    
    Color();
    Color(std::string);
    Color(uint8_t, uint8_t, uint8_t);
    Color(uint8_t, uint8_t, uint8_t, uint8_t);

    void SetHSV(float, float, float);

    friend Color operator+(const Color&, const Color&);
    Color& operator+=(const Color&);
    
    friend Color operator-(const Color&, const Color&);
    Color& operator-=(const Color&);

    SDL_Color ColorSDL();

};

#endif// FOG_COLOR
