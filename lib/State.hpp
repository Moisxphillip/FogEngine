#ifndef FOG_STATE
#define FOG_STATE

#include "../lib/Tools.hpp"
#include "../lib/Sprite.hpp"
#include "../lib/Music.hpp"

class State
{
    private:
        Sprite _StateBg;
        Music _StateMusic;
        bool _QuitRequested;

    public:
        State();
        bool QuitRequested();
        void LoadAssets();
        void Update(float);
        void Render();

    protected:

};


#endif//FOG_STATE