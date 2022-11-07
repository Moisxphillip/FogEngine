#include "../lib/Game.hpp"

Game* Game::_GameInstance = nullptr;

void Error(std::string Info)
{
    std::cout << "Error! " << Info << ".\n";
    std::cout << SDL_GetError() << ".\n";
}

void Game::_GameInitSystems()
{
    //init SDL
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0)
    {
        Error("SDL could not be initialized");
    }
    
    //init Image, Initialized systems = return flags
    if(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) 
                != (IMG_INIT_JPG | IMG_INIT_PNG))
    {
        Error("IMG could not initialize one of its dependencies");
    }

    //init Audio, Initialized systems = return flags
    if(Mix_Init(MIX_INIT_FLAC | MIX_INIT_OGG | MIX_INIT_MP3) 
                != (MIX_INIT_FLAC | MIX_INIT_OGG | MIX_INIT_MP3))
    {
        Error("Mix could not initialize one of its dependencies");
    }

    if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0)
    {
        Error("OpenAudio could not be initialized");
    }
    
    Mix_AllocateChannels(32); //Channel allocation for different audio tracks


    //TODO refactor and place on the appropriate place
    _GameWindow = SDL_CreateWindow(_GameTitle.c_str(), SDL_WINDOWPOS_CENTERED, 
    SDL_WINDOWPOS_CENTERED, _GameWidth, _GameHeight, SDL_WINDOW_SHOWN);
    if(_GameWindow == nullptr)
    {
        Error("Window could not be created");   
    }
}

Game::Game(std::string Name = "FogEngine", int Width = 1024, int Height = 600)
{
    //Register window info
    _GameTitle = Name;
    _GameWidth = Width;
    _GameHeight = Height;

    //Check if there is another instance working already
    if(_GameInstance != nullptr)
    {
        Error("Instance already exists");
    }

    _GameInitSystems();

}

Game::~Game()
{
    //Free resources
    SDL_DestroyWindow(_GameWindow);

    //Quit SDL subsystems
    SDL_Quit();
    IMG_Quit();
    Mix_Quit();
    delete _GameInstance;
}

void Game::Run()
{
    SDL_Surface* _GameSurface;
    _GameSurface = SDL_GetWindowSurface(_GameWindow);
    //Fill the surface white
    SDL_FillRect( _GameSurface, NULL, SDL_MapRGB( _GameSurface->format, 0xFF, 0x00, 0x00 ) );
    //Update the surface
    SDL_UpdateWindowSurface(_GameWindow);
    //a hack to get window to stay up
    SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }
}

SDL_Renderer* Game::GetRenderer()
{
    return _GameRenderer;
}

State& Game::GetState()
{
    return *_GameState;
}

Game& Game::GetInstance()
{
    if(_GameInstance == nullptr)
    {
        _GameInstance = new Game("FogEngine", 1024, 600);
    }
    return *_GameInstance;
}