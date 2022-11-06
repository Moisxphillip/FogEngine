#ifndef FOG_GAME
#define FOG_GAME

#include <string>
#include "../lib/Xrand.hpp"
#include "../sdl/include/SDL2/SDL.h"
#include "../sdl/include/SDL2/SDL_mixer.h"
#include "../sdl/include/SDL2/SDL_image.h"
#include "../sdl/include/SDL2/SDL_ttf.h"


class Game
{
    public:
        Game();
        Game(std::string, int, int);
        ~Game();
        void Run();
        
    private:
        int WindowWidth, WindowHeight;
        std::string WindowTitle;
                    
    protected:

};

Game::Game(std::string Name, int Width, int Height)
{
    
}

Game::Game()
{

}

Game::~Game()
{

}

void Game::Run()
{

}

#endif//FOG_GAME