#ifndef FOG_COMPONENT
#define FOG_COMPONENT

#include "../lib/IncludeAll.hpp"

class Component
{
    protected:
        GameObject& GameObjAssoc;

    public:
        Uses ComponentFlags;
        Component(GameObject&);
        virtual ~Component();
        virtual void Update(float);
        virtual void Collided(GameObject&);
        virtual void Render();
        virtual void Start();
        virtual bool Is(std::string);

};

#endif//FOG_COMPONENT