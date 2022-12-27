#include "../lib/IncludeAll.hpp"


void Error(std::string Info)
{
    std::cout << "Error! " << Info << ".\n";
    std::cout << SDL_GetError() << ".\n";
    //TODO call exit(-1) on error
}

int Fps(int Rate) //Takes intended frames per second and returns approximated time of each frame
{
    return 1000/Rate;
}

double WrapMax(double Val, double Max)
{
    return fmod(Max + fmod(Val, Max), Max);
}

//Val -> [Min,Max)
double WrapMinMax(double Val, double Min, double Max)
{
    return Min + WrapMax(Val - Min, Max - Min);
}