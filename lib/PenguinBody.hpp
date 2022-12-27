#ifndef FOG_PENGBODY
#define FOG_PENGBODY

#include "../lib/IncludeAll.hpp"

class PenguinBody : public Component
{
    private:
        std::weak_ptr<GameObject> _Cannon;
        Vec2 _Speed;
        float _LinearSpeed;
        float _Angle;
        int _HP;

    public:
        static PenguinBody* Player;

        PenguinBody(GameObject&);
        ~PenguinBody();

        bool Is(std::string);
        void Render();
        void Start();
        void Update(float);

};

#endif//FOG_PENGBODY