#ifndef FOG_STATE
#define FOG_STATE

#include "../lib/IncludeAll.hpp"

class State
{
    private:
        Music *_StateMusic;
        bool _QuitRequested;
        bool _QuitFade;
        void _Input();
        void _AddObject(int, int);
        std::vector<std::shared_ptr<GameObject>> GameObjVec;
        bool _Started;

    public:
        XrandU64 Rng;

        State();
        ~State();
        Camera Cam;

        void Start();
        std::weak_ptr<GameObject> AddGameObj(GameObject*);
        std::weak_ptr<GameObject> GetGameObjPtr(GameObject*);
        bool QuitRequested();
        void LoadAssets();
        void Input();
        void Update(float);
        void Render();

};


#endif//FOG_STATE