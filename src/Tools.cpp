#include "../lib/IncludeAll.hpp"


void Error(std::string Info)
{
    std::cout << "Error! " << Info << ".\n";
    std::cout << SDL_GetError() << ".\n";
}

int Fps(int Rate) //Takes intended frames per second and returns approximated time of each frame
{
    return 1000/Rate;
}