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
        bool TargetsPlayer;
        Bullet(GameObject&, float, float, int, float, std::string, int, bool, bool);
        int GetDamage();

        void Collided(GameObject&);
        bool Is(std::string);
        void Render();
        void Start();
        void Update(float);
};

#endif//FOG_BULLET
