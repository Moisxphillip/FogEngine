#ifndef FOG_COLLIDER
#define FOG_COLLIDER

#include "../lib/IncludeAll.hpp"

class Collider : public Component
{
    private:
        Vec2 _Scale;
        Vec2 _Offset;

    public:
        Rect Box;
        
        Collider(GameObject&);
        Collider(GameObject&, Vec2, Vec2);
        
        void SetScale(Vec2);
        void SetOffset(Vec2);

        bool Is(std::string);
        void Render();
        void Start();
        void Update(float);

};

#endif//FOG_COLLIDER