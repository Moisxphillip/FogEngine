#ifndef FOG_INPUT
#define FOG_INPUT

#include "../lib/IncludeAll.hpp"

#define K_LEFTARROW SDLK_LEFT
#define K_RIGHTARROW SDLK_RIGHT
#define K_UPARROW SDLK_UP
#define K_DOWNARROW SDLK_DOWN
#define K_ENTER SDLK_RETURN
#define K_SPACE SDLK_SPACE

#define K_W  SDLK_w
#define K_A SDLK_a
#define K_S SDLK_s
#define K_D SDLK_d
#define K_B SDLK_b
#define K_P SDLK_p

#define K_ESC SDLK_ESCAPE
#define M_LEFT SDL_BUTTON_LEFT
#define M_RIGHT SDL_BUTTON_RIGHT

class InputManager
{
    private:
        InputManager();
        ~InputManager();
        static InputManager* _InputM;
        
        bool _QuitRequested;
        int _UpdateCounter;

        bool _KeyState[FOG_KEYARR];
        int _KeyUpdate[FOG_KEYARR];
        
        bool _MouseState[FOG_BUTTONARR];
        int _MouseUpdate[FOG_BUTTONARR];
        int _MouseX;
        int _MouseY;
        
    public:
        //Copy prevention
        InputManager(const InputManager&) = delete;
        void operator=(InputManager &InputMg)= delete;

        void Update();
        bool QuitRequested();
        static InputManager& GetInstance();
        
        bool KeyPress(int);
        bool KeyRelease(int);
        bool IsKeyDown(int);

        bool MousePress(int);
        bool MouseRelease(int);
        bool IsMouseDown(int);
        int GetMouseX();
        int GetMouseY();
        Vec2 GetMouseVec2();

};

#endif//FOG_INPUT