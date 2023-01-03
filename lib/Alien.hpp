#ifndef FOG_ALIEN
#define FOG_ALIEN

#include "../lib/IncludeAll.hpp"

class Alien : public Component
{
    private:
        enum AlienState
        {
            MOVING,
            REST            
        };
        AlienState _CurrState;

        Timer _Rest;
        Vec2 Destination;
        Vec2 _Speed;
        int _HP;
        int _NumMinions;
        std::vector<std::weak_ptr<GameObject>> _MinionVec;

    public:
        static int AlienCount;
        Alien(GameObject&, int);
        ~Alien();
        
        void Collided(GameObject&);
        bool Is(std::string);
        void Render();
        void Start();
        void Update(float);

};


#endif//FOG_ALIEN