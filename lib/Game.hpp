#ifndef FOG_GAME
#define FOG_GAME

#include "../lib/IncludeAll.hpp"

class Game
{
    private:
        //Name and size
        int _GameWidth;
        int _GameHeight;
        std::string _GameTitle;
        int _MixChannels;
        
        //internal procedures
        void _GameInitSDL();
        
        //Mandatory
        Game(std::string, int, int);
        static Game* _GameInstance;
        SDL_Window* _GameWindow = nullptr;
        SDL_Renderer* _GameRenderer = nullptr;
        State* _GameState = nullptr;

    public:
        //Copy prevention
        Game(const Game&) = delete;
        void operator=(Game &game)= delete;

        //Mandatory
        ~Game();
        void Run();
        SDL_Renderer* GetRenderer();
        State& GetState();
        static Game& GetInstance();

};



#endif//FOG_GAME