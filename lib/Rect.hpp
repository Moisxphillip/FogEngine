#ifndef FOG_RECT
#define FOG_RECT

#include "../lib/IncludeAll.hpp"

class Vec2;

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
        void SetCenter(Vec2);
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