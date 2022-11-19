#ifndef FOG_STATE
#define FOG_STATE

#include "../lib/Tools.hpp"
#include "../lib/Sprite.hpp"
#include "../lib/Music.hpp"
#include "../lib/Path.hpp"

class State
{
    private:
        Sprite *_StateBg;
        Music *_StateMusic;
        bool _QuitFade;
        bool _QuitRequested;

    public:
        State();
        ~State();

        bool QuitRequested();
        void LoadAssets();
        void Update(float);
        void Render();

};


#endif//FOG_STATE