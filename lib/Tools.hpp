#ifndef FOG_TOOLS
#define FOG_TOOLS

#include <iostream>
#include <string>
#define SDL_BASE
#define SDL_IMAGE
#define SDL_MIXER
#define SDL_TTF
#include "../lib/IncludeSDL.hpp"

void Error(std::string);
int Fps(int);

#endif//FOG_TOOLS