#ifndef FOG_RECT
#define FOG_RECT

#include <iostream>
#include "../lib/Vec2.hpp"

class Rect
{
    public:
        //Variables
        float x, y, w, h;
        Vec2 CenterV;
        //Constructors
        Rect(float, float, float, float);
        Rect();
        //Functions
        void AddVec2(const Vec2&);
        Vec2 Center();
        float DistCenters(const Rect&);
        bool Contains(const Vec2&);
        //+, -, <<
        friend Rect operator+(const Rect&, const Vec2&);
        friend Rect operator-(const Rect&, const Vec2&);
        friend std::ostream& operator<<(std::ostream&, const Rect&);
        //+=, -=,
        Rect& operator+=(const Vec2&);
        Rect& operator-=(const Vec2&);

};



#endif//FOG_RECT