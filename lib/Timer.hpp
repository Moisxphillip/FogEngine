#ifndef FOG_TIMER
#define FOG_TIMER

#include "../lib/IncludeAll.hpp"

class Timer
{
    private:
        float _Time;

    public:
        Timer();
        float Get();
        void Update(float);
        void Restart();
};

#endif//FOG_TIMER