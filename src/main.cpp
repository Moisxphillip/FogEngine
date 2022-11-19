#include "../lib/IncludeAll.hpp"

int main (int argc, char** argv) 
{
    Game::GetInstance().Run(); //Create a game instance by calling Get.. then run it

    return 0;
}