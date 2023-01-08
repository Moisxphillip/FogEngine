#ifndef FOG_TITLESTATE
#define FOG_TITLESTATE

#include "../lib/IncludeAll.hpp"


class TitleState : public State
{
    private:
        Timer TextColorChange;
        Color TextColor;
        
    public:
        TitleState();
        ~TitleState();

        void LoadAssets();
        void Update(float);
        void Render();

        void Start();
        void Pause();
        void Resume();

};


#endif//FOG_TITLESTATE