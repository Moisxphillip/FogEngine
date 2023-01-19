#ifndef FOG_VERTEX
#define FOG_VERTEX

#include "../lib/IncludeAll.hpp"

struct Position
{
    float X;
    float Y;
};

struct Colors
{
    uint8_t R;
    uint8_t G;
    uint8_t B;
    uint8_t A;
};

struct UV
{
    float U;
    float V;
};

struct Vertex
{
    Position Pos;
    Colors Colors;
    UV Uv;
    void SetColors(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    {
        Colors.R = r;
        Colors.G = g;
        Colors.B = b;
        Colors.A = a;
    }
    void SetPos(float x, float y)
    {
        Pos.X = x;
        Pos.Y = y;
    }
    void SetUV(float u, float v)
    {
        Uv.U = u;
        Uv.V = v;
    }
};

#endif// FOG_VERTEX