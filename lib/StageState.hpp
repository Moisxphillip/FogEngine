#ifndef FOG_STAGESTATE
#define FOG_STAGESTATE

#include "../lib/IncludeAll.hpp"

class StageState : public State
{
    private:
        Music *_StateMusic;
        bool _QuitFade;
        void _FadeOut();
        
    public:
        XrandU64 Rng;

        StageState();
        ~StageState();

        void LoadAssets();

        void Start();
        void Pause();
        void Resume();
        void Update(float);
        void Render();

};


#endif//FOG_STAGESTATE