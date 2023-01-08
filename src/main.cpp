#include "../lib/IncludeAll.hpp"

int main (int argc, char** argv) 
{
    TitleState* Begin = new TitleState();
    Game::GetInstance().Push(Begin);
    Game::GetInstance().Run(); //Create a game instance by calling Get.. then run it

    return 0;
}