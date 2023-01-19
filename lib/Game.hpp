#ifndef FOG_GAME
#define FOG_GAME

#include "../lib/IncludeAll.hpp"

enum class GameState{PLAY, EXIT};

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
        bool _ChangeState();
        
        //Mandatory
        Game(std::string, int, int);
        static Game* _GameInstance;
        SDL_Window* _GameWindow = nullptr;
        SDL_Renderer* _GameRenderer = nullptr;
        State* _GameState = nullptr;
        std::stack<std::unique_ptr<State>> StateStack;

        int _FrameStart;
        float _Dt;
        void _CalculateDt();

        GameState _CurrState;

    public:
        //Copy prevention
        Game(const Game&) = delete;
        void operator=(Game &game)= delete;

        //Mandatory
        ~Game();
        void Run();

        void GLRun();
        void _ManageInput();
        void _DrawGame();

        void Push(State*);
        SDL_Renderer* GetRenderer();
        State& GetState();
        static Game& GetInstance();
        float GetDt();

};



#endif//FOG_GAME