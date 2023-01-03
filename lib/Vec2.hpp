#ifndef FOG_VEC2
#define FOG_VEC2

#include "../lib/IncludeAll.hpp"

class Vec2
{
    public:
        //Variables
        float x, y;
        //Constructors
        Vec2();
        Vec2(float, float);
        //Vector special operations
        float Magnitude();
        float Angle();
        Vec2 Normalized();
        float Dot(const Vec2&);
        float Distance(const Vec2&);
        Vec2 DistVec2(const Vec2&);
        float DistAngle(const Vec2&);
        Vec2 Rotate(const float&);
        //Useful functions for external use
        static float Dot(const Vec2&, const Vec2&);
        static float Distance(const Vec2&, const Vec2&);
        static Vec2 DistVec2(const Vec2&, const Vec2&);
        static float DistAngle(const Vec2&, const Vec2&);
        static float DegToRad(const float&);
        static float RadToDeg(const float&);
        //Operation overloads
        friend Vec2 operator+(const Vec2&, const Vec2&);
        friend Vec2 operator-(const Vec2&, const Vec2&);
        friend Vec2 operator*(const Vec2&, const float&);
        friend Vec2 operator*(const Vec2&, const Vec2&);
        friend bool operator==(const Vec2&, const Vec2&);
        friend bool operator!=(const Vec2&, const Vec2&);
        friend std::ostream& operator<<(std::ostream&, const Vec2&);
        //=
        Vec2& operator=(const std::list<float>&);
        Vec2& operator=(const std::list<int>&);
        //+=, -=, *=
        Vec2& operator+=(const Vec2&);
        Vec2& operator-=(const Vec2&);
        Vec2& operator*=(const float&);
        Vec2& operator*=(const Vec2&);

};  

#endif//FOG_VEC2