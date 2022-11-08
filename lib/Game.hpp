#ifndef FOG_GAME
#define FOG_GAME

//C++ Libs
#include <iostream>
#include <string>

//Local libs
#include "../lib/Tools.hpp"
#include "../lib/Xrand.hpp"
#include "../lib/State.hpp"


//SDL Libs
#define SDL_BASE
#define SDL_IMAGE
#define SDL_MIXER
#define SDL_TTF
#include "../lib/IncludeSDL.hpp"




class Game
{
    private:
        //Name and size
        int _GameWidth;
        int _GameHeight;
        std::string _GameTitle;
        //internal procedures
        void _GameInitSystems();
        
        //Mandatory
        Game(std::string, int, int);
        static Game* _GameInstance;
        SDL_Window* _GameWindow = nullptr;
        SDL_Renderer* _GameRenderer = nullptr;
        State* _GameState = nullptr;

    public:              
        Game(const Game&) = delete;
        ~Game();
        void Run();
        SDL_Renderer* GetRenderer();
        State& GetState();
        static Game& GetInstance();

    protected:

};



#endif//FOG_GAME