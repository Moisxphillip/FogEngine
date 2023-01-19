#include "../lib/IncludeAll.hpp"

//Set value for singleton class
Game* Game::_GameInstance = nullptr;

void Game::_GameInitSDL()
{
    //init SDL
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_EVERYTHING) != 0)
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

    if(TTF_Init() != 0)
    {
        Error("Game::_GameInitSDL: TTF_Init could not be initialized");
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
    SDL_WINDOWPOS_CENTERED, _GameWidth, _GameHeight, SDL_WINDOW_OPENGL| SDL_WINDOW_RESIZABLE);
    if(_GameWindow == nullptr)
    {
        Error("Game::Game: Window could not be created");   
    }
    
    //GL Context to run window
    SDL_GLContext GLCont = SDL_GL_CreateContext(_GameWindow);
    if(GLCont == nullptr) 
    {
        Error("Game::Game: GLContext could not be created");   
    }
    if(glewInit() != GLEW_OK)
    {
        Error("Game::Game: glewInit failed a component init");
    }
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); //Double buffer to prevent stuttering
    glClearColor(0,0.3,1, 1.0);//Sets the color of clear buffer

    // Renderer creation
    // -1 allows SDL to choose the most appropriate render drive
    _GameRenderer = SDL_CreateRenderer(_GameWindow, -1, SDL_RENDERER_ACCELERATED);
    if(_GameRenderer == nullptr) 
    {
        Error("Game::Game: Renderer could not be created");   
    }
    SDL_RenderSetLogicalSize(_GameRenderer, FOG_RENDERDIMENSIONS);

    _FrameStart = SDL_GetTicks();
    _Dt = 0.0f;
    _CurrState = GameState::PLAY;
    _GameState = nullptr;//new StageState; //Creates a base state for the game 
}

Game::~Game()
{
    //Clear memory used by Resources class
    Resources::FlushContext();

    //Quit SDL subsystems
    TTF_Quit();
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_DestroyRenderer(_GameRenderer);
    SDL_DestroyWindow(_GameWindow);
    SDL_Quit();
    
    //Free last resources
    while(!StateStack.empty())
    {
        StateStack.pop();
    }

    if(_GameState != nullptr)
    {
        delete _GameState;
        _GameState = nullptr;
    }
    delete _GameInstance;
}

bool Game::_ChangeState()
{
    if(_GameState != nullptr)
    {
        if(!StateStack.empty())
        {
            StateStack.top()->Pause();
        }
        StateStack.push(std::unique_ptr<State>(_GameState));
        _GameState = nullptr;
        return true;
    } 
    return false;
}

GameObject X;
SpriteGL* Figure = new SpriteGL(X);
GLSL _GLColor;
float _Time = 0;
GLTexture _Tex;

void Game::GLRun()
{

    Figure->Init(-0.5,-0.5,1,1);
    _Tex = IO::LoadPNG(FIMG_PENGFACE);
    _GLColor.CompileShaders("./shader/ColorShading.vert", "./shader/ColorShading.frag");
    _GLColor.AddAttribute("VertexPosition");
    _GLColor.AddAttribute("VertexColor");
    _GLColor.AddAttribute("VertexUV");
    _GLColor.LinkShaders();
    while(!InputManager::GetInstance().QuitRequested())
    {
        _CalculateDt();
        InputManager::GetInstance().Update();
        _Time += GetDt();
        _DrawGame();
        SDL_Delay(Fps(30));//controls the framerate
    }
}

void Game::_DrawGame()
{
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//Clearing buffers to insert new info
    _GLColor.Bind();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _Tex.ID);
    GLint TexLocation = _GLColor.GetUniformLocation("SpriteSampler");
    glUniform1i(TexLocation, 0);
    
    GLint TimeLocation = _GLColor.GetUniformLocation("Time");
    if((GLuint)TimeLocation != GL_INVALID_INDEX)
    {
        glUniform1f(TimeLocation, _Time);
    }

    Figure->Render();

    glBindTexture(GL_TEXTURE_2D, 0);
    _GLColor.Unbind();
    SDL_GL_SwapWindow(_GameWindow);
}

void Game::Run()
{   
    _ChangeState();
    while(!StateStack.empty() && !StateStack.top()->QuitRequested())    //Wait for quit state
    {
        if(!StateStack.top()->HasStarted())
        {
            StateStack.top()->Start();
        }
        else
        {
            StateStack.top()->Resume();
        }

        while(!StateStack.top()->PopRequested())
        {
            _CalculateDt();
            InputManager::GetInstance().Update();
            StateStack.top()->Update(GetDt());//Calls update for all GameObject inside a scene
            StateStack.top()->Render(); //Calls render for all GameObject...
            SDL_RenderPresent(_GameRenderer);//Presents the new rendered stuff on screen
            SDL_Delay(Fps(30));//controls the framerate
            if(_ChangeState())
            {
                break;
            }
        }
        if(StateStack.top()->PopRequested())
        {
            bool QuitRequested = StateStack.top()->QuitRequested();
            StateStack.pop();
            if(QuitRequested && !StateStack.empty())
            {
                StateStack.top()->RequestQuit();
            }
        }
    }  
}

SDL_Renderer* Game::GetRenderer()
{
    return _GameRenderer;
}

State& Game::GetState()
{
    return *StateStack.top().get();
}

void Game::Push(State* NewState)
{
    _GameState = NewState;
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