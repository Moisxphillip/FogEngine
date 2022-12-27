#ifndef FOG_PENGCANNON
#define FOG_PENGCANNON

#include "../lib/IncludeAll.hpp"

class PenguinCannon : public Component
{
    private:
        std::weak_ptr<GameObject> _Body;
        float _Angle;

    public:
        PenguinCannon(GameObject&, std::weak_ptr<GameObject>);
        void Shoot();
        bool Is(std::string);
        void Render();
        void Start();
        void Update(float);

};

#endif//FOG_PENGCANNON