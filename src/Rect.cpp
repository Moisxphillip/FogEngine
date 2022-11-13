#include "../lib/Rect.hpp"



Rect::Rect(int x, int y, int w, int h)
{
  this->x = x;
  this->y = y;
  this->w = w;
  this->h = h;
}

Rect::Rect()
{
    Rect(0, 0, 0, 0);
}