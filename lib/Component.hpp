#ifndef FOG_COMPONENT
#define FOG_COMPONENT

#include "../lib/GameObject.hpp"
#include <string>

class Component
{
    protected:
        GameObject& GameObjAssoc;

    public:
        Component(GameObject&);
        virtual ~Component();
        virtual void Update(float);
        virtual void Render();
        virtual bool Is(std::string);

};

#endif//FOG_COMPONENT