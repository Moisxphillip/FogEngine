#include "../lib/IncludeAll.hpp"


//Set value for singleton class
Game* Game::_GameInstance = nullptr;

void Game::_GameInitSDL()
{
    //init SDL
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0)
    {
        Error("Game::_GameInitSDL: SDL could not be initialized");
    }
    
    //init Image, Initialized systems = return flags
    if(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) 
                != (IMG_INIT_JPG | IMG_INIT_PNG))
    {
        Error("Game::_GameInitSDL: IMG could not initialize one of its dependencies");
    }

    //init Audio, Initialized systems = return flags
    if(Mix_Init(MIX_INIT_FLAC | MIX_INIT_OGG | MIX_INIT_MP3) 
                != (MIX_INIT_FLAC | MIX_INIT_OGG | MIX_INIT_MP3))
    {
        Error("Game::_GameInitSDL: Mix could not initialize one of its dependencies");
    }

    if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0)
    {
        Error("Game::_GameInitSDL: OpenAudio could not be initialized");
    }
    
    if(Mix_AllocateChannels(_MixChannels) < _MixChannels) //Channel allocation for different audio tracks
    {
        Error("Game::_GameInitSDL: Mix_AllocateChannels could not allocate the requested number of channels");
    }
}

Game::Game(std::string Name = "FogEngine", int Width = 1024, int Height = 600)
{
    //Register window info
    _GameTitle = Name;
    _GameWidth = Width;
    _GameHeight = Height;
    _MixChannels = 32;
    
    if(_GameInstance != nullptr)//Report error if there is another instance working already
    {
        Error("Game::Game: Instance already exists");
        return;
    }
    else 
    {
        _GameInstance = this;
    }

    //Init SDL Resources
    _GameInitSDL();

    //Window creation
    _GameWindow = SDL_CreateWindow(_GameTitle.c_str(), SDL_WINDOWPOS_CENTERED, 
    SDL_WINDOWPOS_CENTERED, _GameWidth, _GameHeight, SDL_WINDOW_SHOWN);
    if(_GameWindow == nullptr)
    {
        Error("Game::Game: Window could not be created");   
    }
    std::cout << "Game::Game: Window created\n";
    
    //Renderer creation
    //-1 allows SDL to choose the most appropriate render drive
    _GameRenderer = SDL_CreateRenderer(_GameWindow, -1, SDL_RENDERER_ACCELERATED);
    if(_GameRenderer == nullptr) 
    {
        Error("Game::Game: Renderer could not be created");   
    }
    std::cout << "Game::Game: Renderer created\n";

    _GameState = new State;
}

Game::~Game()
{
    //Quit SDL subsystems
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_DestroyRenderer(_GameRenderer);
    SDL_DestroyWindow(_GameWindow);
    SDL_Quit();
    
    //Free last resources
    delete _GameState;
    delete _GameInstance;
}

void Game::Run()
{
    //The quit state is sent by the alt+f4 command or by clicking on 'x'
    _GameState->LoadAssets();

    while(!_GameState->QuitRequested())
    {
        _GameState->Update(0);
        _GameState->Render();
        SDL_RenderPresent(_GameRenderer);
        SDL_Delay(Fps(30));
    }
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
        _GameInstance = new Game(FOG_SCRTITLE, FOG_SCRWIDTH, FOG_SCRHEIGHT);
    }
    return *_GameInstance;
}