#ifndef FOG_BULLET
#define FOG_BULLET

#include "../lib/IncludeAll.hpp"


class Bullet : public Component
{
    private:
        Vec2 _Speed;
        float _DistanceLeft;
        int _Damage;
            
    public:
        Bullet(GameObject&, float, float, int, float, std::string);
        void Update(float);
        void Render();
        bool Is(std::string);
        void Start();
        int GetDamage();
};

#endif//FOG_BULLET
