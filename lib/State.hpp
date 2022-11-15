#ifndef FOG_STATE
#define FOG_STATE

#include <vector>
#include <memory>

#include "../lib/Tools.hpp"
#include "../lib/Sprite.hpp"
#include "../lib/Music.hpp"
#include "../lib/Path.hpp"

class State
{
    private:
        Sprite *_StateBg;
        Music *_StateMusic;
        bool _QuitRequested;
        void _Input();
        void _AddObject();
        std::vector<std::unique_ptr<GameObject>> GameObjVec;

    public:
        State();
        ~State();

        bool QuitRequested();
        void LoadAssets();
        void Update(float);
        void Render();

};


#endif//FOG_STATE