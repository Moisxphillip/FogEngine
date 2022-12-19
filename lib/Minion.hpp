#ifndef FOG_MINION
#define FOG_MINION

#include "../lib/IncludeAll.hpp"

class Minion : public Component
{
    private:
        std::weak_ptr<GameObject> _AlienCenter;
        float _Arc;

    public:
        Minion(GameObject&, std::weak_ptr<GameObject>, float);
        void Shoot(Vec2);
        bool Is(std::string);
        void Render();
        void Start();
        void Update(float);

};

#endif//FOG_MINION
