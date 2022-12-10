#include "../lib/IncludeAll.hpp"

#define PI_DEG 0.0174532925199432957692f
#define DEG_PI 57.295779513082320876798f

Vec2::Vec2(float x, float y)
{
    this->x = x;
    this->y = y;
}

Vec2::Vec2()
{
    Vec2(0.0, 0.0);
}
//_____________________________________

float Vec2::Magnitude()
{
    return sqrt((this->x * this->x) + (this->y * this->y));
}

float Vec2::Angle()
{
    return atan2(this->y, this->x);
}

Vec2 Vec2::Normalized()
{
    float Mag = this->Magnitude();
    if(Mag == 0)
    {
        std::cout << "Vec2::Normalized: Division by zero must not occur"; //TODO change to Error() from Tools.hpp when joined to main project
        return Vec2(0,0);
    }
    return Vec2(this->x/Mag, this->y/Mag);
}

float Vec2::Dot(const Vec2& Vector)
{
    return (this->x* Vector.x + this->y*Vector.y);
}

float Vec2::Distance(const Vec2& Vector)
{
    return ((*this - Vector).Magnitude());
}

Vec2 Vec2::DistVec2(const Vec2& Vector)
{
    return (Vector - *this);
}

float Vec2::DistAngle(const Vec2& Vector)
{
    return ((Vector - *this).Angle());
}

void Vec2::Rotate(const float& Rad)
{
    float Sin = sin(Rad), Cos = cos(Rad);
    float x = this->x*Cos + this->y*Sin;
    float y = this->y*Cos - this->x*Sin;
    this->x = x;
    this->y = y;
}

//________________________________________
float Vec2::Dot(const Vec2& Vector1, const Vec2& Vector2)
{
    return (Vector1.x* Vector2.x + Vector1.y*Vector2.y);
}

float Vec2::Distance(const Vec2& Vector1, const Vec2& Vector2)
{
    return ((Vector1 - Vector2).Magnitude());
}

Vec2 Vec2::DistVec2(const Vec2& Vector1, const Vec2& Vector2)
{
    return (Vector2-Vector1);
}

float Vec2::DistAngle(const Vec2& Vector1, const Vec2& Vector2)
{
    return ((Vector2-Vector1).Angle());
}

inline float Vec2::DegToRad(const float& Deg)
{
    return (Deg*PI_DEG);
}

inline float Vec2::RadToDeg(const float& Rad)
{
    return (Rad*DEG_PI);
}

//_________________________________________________

Vec2 operator+(const Vec2& Vector1, const Vec2& Vector2)
{
    return Vec2(Vector1.x + Vector2.x, Vector1.y + Vector2.y);
}

Vec2 operator-(const Vec2& Vector1, const Vec2& Vector2)
{
    return Vec2(Vector1.x - Vector2.x, Vector1.y - Vector2.y);
}

Vec2 operator*(const Vec2& Vector1, const float& Scalar)
{
    return Vec2(Vector1.x * Scalar, Vector1.y * Scalar);
}

bool operator==(const Vec2& Vector1, const Vec2& Vector2)
{
    return (((abs(Vector1.x-Vector2.x) < 1e-9) && (abs(Vector1.y-Vector2.y) < 1e-9)) ? true : false);
}

bool operator!=(const Vec2& Vector1, const Vec2& Vector2)
{
    return !(Vector1 == Vector2);
}

std::ostream& operator<<(std::ostream& Out, const Vec2& Vector)
{
    Out << "(" << Vector.x << " , " << Vector.y << ")";
    return Out;
}

//___________________________________________

Vec2& Vec2::operator=(const std::list<float>& List)
{
    this->x = List.front();
    this->y = List.back();
    return *this;
}

Vec2& Vec2::operator=(const std::list<int>& List)
{
    this->x = float(List.front());
    this->y = float(List.back());
    return *this;
}

Vec2& Vec2::operator+=(const Vec2& Vector)
{
    this->x = this->x + Vector.x;
    this->y = this->y + Vector.y;
    return *this;
}

Vec2& Vec2::operator-=(const Vec2& Vector)
{
    this->x = this->x - Vector.x;
    this->y = this->y - Vector.y;
    return *this;
}

Vec2& Vec2::operator*=(const float& Scalar)
{
    this->x = this->x * Scalar;
    this->y = this->y * Scalar;
    return *this;
}