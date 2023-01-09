#ifndef FOG_ENDSTATE
#define FOG_ENDSTATE

#include "../lib/IncludeAll.hpp"


class EndState : public State
{
    private:
        Timer TextColorChange;
        Color TextColor;
        Music* _EndMusic;
        
    public:
        EndState();
        ~EndState();

        void LoadAssets();
        void Update(float);
        void Render();

        void Start();
        void Pause();
        void Resume();

};


#endif//FOG_ENDSTATE