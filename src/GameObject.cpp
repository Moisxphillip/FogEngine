#include "../lib/IncludeAll.hpp"

//TODO future improvement: sort component vector on new addition, implement binary search for Get/Remove;

GameObject::GameObject()
{
    Box = Rect(0,0,0,0);
    _GameObjDead = false;
}

GameObject::~GameObject()
{
    _GameObjComponents.clear();    
}

void GameObject::Update(float Dt)
{
    for (int i = 0; i < _GameObjComponents.size(); i++)
    {
        _GameObjComponents[i]->Update(Dt);
    }  
}

void GameObject::Render()
{
    for (int i = 0; i < _GameObjComponents.size(); i++)
    {
        _GameObjComponents[i]->Render();
    }
}

bool GameObject::IsDead()
{
    return _GameObjDead;
}

void GameObject::RequestDelete()
{
    _GameObjDead = true;
}

void GameObject::AddComponent(Component* GameComponent)
{
    _GameObjComponents.emplace_back(GameComponent);
}

void GameObject::RemoveComponent(Component* GameComponent)
{

    for (int i = 0; i < _GameObjComponents.size(); i++)
    {
        if(_GameObjComponents[i].get() == GameComponent)
        {
            _GameObjComponents.erase(_GameObjComponents.begin()+i);
            return;
        }
    }
}

Component* GameObject::GetComponent(std::string ComponentName)
{
    for (int i = 0; i < _GameObjComponents.size(); i++)
    {
        if(_GameObjComponents[i]->Is(ComponentName))
        {
            return _GameObjComponents[i].get();
        }
    }
    return nullptr;
}
