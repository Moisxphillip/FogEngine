#include "../lib/IncludeAll.hpp"

Rect::Rect(float x, float y, float w, float h)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    CenterV = Vec2(0, 0);
    this->CenterV = this->Center();
}

Rect::Rect()
{
    Rect(0, 0, 0, 0);
}

void Rect::AddVec2(const Vec2& Vector)
{
    this->x += Vector.x;
    this->y += Vector.y;
}

Vec2 Rect::Center()
{
    return Vec2(x+(w/2), y+(h/2));
}

void Rect::SetCenter(Vec2 Coord)
{
    this->x = Coord.x - w/2;
    this->y = Coord.y - h/2;
}

float Rect::DistCenters(const Rect& Rectangle)
{
    return (this->CenterV - Rectangle.CenterV).Magnitude();
}

bool Rect::Contains(const Vec2& Vector)
{
    return ((Vector.x >= this->x) 
        && (Vector.y >= this->y)
        && (Vector.x <= (this->x+this->w))
        && (Vector.y <= (this->y+this->h)));
}       

//+, -, <<
Rect operator+(const Rect& Rectangle, const Vec2& Vector)
{
    return Rect(Rectangle.x + Vector.x, Rectangle.y + Vector.y, Rectangle.w, Rectangle.h);
}

Rect operator-(const Rect& Rectangle, const Vec2& Vector)
{
    return Rect(Rectangle.x - Vector.x, Rectangle.y - Vector.y, Rectangle.w, Rectangle.h);
}

Rect operator*(const Rect& Rectangle, const Vec2& Vector)
{
    return Rect(Rectangle.x * Vector.x, Rectangle.y * Vector.y, Rectangle.w, Rectangle.h);
}

std::ostream& operator<<(std::ostream& Out, const Rect& Rectangle)
{
    Out << '(' << Rectangle.x << ',' << Rectangle.y << "),(" 
    << Rectangle.x << ',' << Rectangle.y+Rectangle.h << "),("
    << Rectangle.x+Rectangle.w << ',' << Rectangle.y+Rectangle.h << "),("
    << Rectangle.x+Rectangle.w << ',' << Rectangle.y << ")";

    return Out;
}

//+=, -=,
Rect& Rect::operator+=(const Vec2& Vector)
{
    *this = *this+Vector;
    this->CenterV = this->Center();
    return *this;
}

Rect& Rect::operator-=(const Vec2& Vector)
{
    *this = *this-Vector;
    this->CenterV = this->Center();
    return *this;
}