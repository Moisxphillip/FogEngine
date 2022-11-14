#ifndef FOG_GAMEOBJ
#define FOG_GAMEOBJ

#include "../lib/Rect.hpp"
#include <vector>

class GameObject
{
    private:
        bool _GameObjDead;
        std::vector<Component*> _GameObjComponents;

    public:
        Rect Box;

        GameObject();
        ~GameObject();

        void Update(float);
        void Render();
        bool IsDead();
        void RequestDelete();
        void AddComponent(Component*);
        void RemoveComponent(Component*);
        Component* GetComponent(std::string);
        
};

#endif//FOG_GAMEOBJ