#ifndef FOG_GAMEOBJ
#define FOG_GAMEOBJ

#include "../lib/IncludeAll.hpp"

class Component;

class GameObject
{
    private:
        bool _GameObjDead;
        std::vector<std::unique_ptr<Component>> _GameObjComponents;

    public:
        Rect Box;
        bool Started;
        float Angle;

        GameObject();
        ~GameObject();
        void Start();
        void Update(float);
        void Render();
        bool IsDead();
        void RequestDelete();
        void AddComponent(Component*);
        void RemoveComponent(Component*);
        Component* GetComponent(std::string);
        
};

#endif//FOG_GAMEOBJ