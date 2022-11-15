#include "../lib/GameObject.hpp"

//future improvement: sort component vector on new addition, implement binary search for Get/Remove;

GameObject::GameObject()
{
    Box = Rect(0,0,0,0);
    _GameObjDead = false;
}

GameObject::~GameObject()
{
    while(!_GameObjComponents.empty())
    {
        delete _GameObjComponents.back(); //TODO refactor to avoid redimensioning
        _GameObjComponents.pop_back() ;
    }
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
    _GameObjComponents.push_back(GameComponent);
}

void GameObject::RemoveComponent(Component* GameComponent)
{
    for (int i = 0; i < _GameObjComponents.size(); i++)
    {
        if(_GameObjComponents[i] == GameComponent)
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
            _GameObjComponents.erase(_GameObjComponents.begin()+i);
            return _GameObjComponents[i];
        }
    }
    return nullptr;
}
