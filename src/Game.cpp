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
    if(_GameInstance != nullptr)//Report error if there is another instance working already
    {
        Error("Game::Game: Instance already exists");
        return;
    }
    else //Register window info
    {
        _GameTitle = Name;
        _GameWidth = Width;
        _GameHeight = Height;
        _MixChannels = FOG_SOUNDCHANNELS;
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
    
    //Renderer creation
    //-1 allows SDL to choose the most appropriate render drive
    _GameRenderer = SDL_CreateRenderer(_GameWindow, -1, SDL_RENDERER_ACCELERATED);
    if(_GameRenderer == nullptr) 
    {
        Error("Game::Game: Renderer could not be created");   
    }

    _FrameStart = SDL_GetTicks();
    _Dt = 0.0f;

    _GameState = new State; //Creates a base state for the game 
}

Game::~Game()
{
    //Clear memory used by Resources class
    Resources::FlushContext();

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
    _GameState->Start();
    while(!_GameState->QuitRequested())    //Wait for quit state
    {
        _CalculateDt();
        InputManager::GetInstance().Update();
        _GameState->Update(GetDt());//Calls update for all GameObject inside a scene
        _GameState->Render(); //Calls render for all GameObject...
        SDL_RenderPresent(_GameRenderer);//Presents the new rendered stuff on screen
        SDL_Delay(Fps(30));//controls the framerate
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
    if(_GameInstance == nullptr) //Only creates a new Game if there's no other instance of the class currently running
    {
        _GameInstance = new Game(FOG_SCRTITLE, FOG_SCRWIDTH, FOG_SCRHEIGHT);
    }
    return *_GameInstance;
}

inline void Game::_CalculateDt()
{
    int FrameEnd = SDL_GetTicks(); //Get Ms count since app start
    _Dt = (FrameEnd - _FrameStart)/1000.0f;//Ms->s is done by the division
    _FrameStart = FrameEnd;
}

inline float Game::GetDt()
{
    return _Dt;
}