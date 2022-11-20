#ifndef FOG_STATE
#define FOG_STATE

#include "../lib/IncludeAll.hpp"

class State
{
    private:
        //Sprite *_StateBg;
        Music *_StateMusic;
        bool _QuitRequested;
        bool _QuitFade;
        void _Input();
        void _AddObject(int, int);
        std::vector<std::unique_ptr<GameObject>> GameObjVec;

    public:
        XrandU64 Rng;

        State();
        ~State();

        bool QuitRequested();
        void LoadAssets();
        void Input();
        void Update(float);
        void Render();

};


#endif//FOG_STATE