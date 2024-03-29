#include "../lib/IncludeAll.hpp"

//TODO future improvement: sort component vector on new addition, implement binary search for Get/Remove;

GameObject::GameObject()
{
    Box = Rect(0,0,0,0); //Inits Object Rectangle
    _GameObjDead = false;//Sets as alive for future checks in the gameObject lifetime
    Started = false;
    Angle = 0;
}

GameObject::~GameObject()
{
    _GameObjComponents.clear();//Removes all components 
}

void GameObject::Start()
{
    for(int i = 0; i < (int)(_GameObjComponents.size()); i++)
    {
        _GameObjComponents[i]->Start();
    }
    Started = true;
}

void GameObject::Update(float Dt)
{
    for (int i = 0; i < (int)(_GameObjComponents.size()); i++)
    {
        _GameObjComponents[i]->Update(Dt);//Calls update from each component belonging to this GameObject
    }

    if(Angle< -M_PI || Angle >M_PI)//Wrapper for avoiding unlimited growth
    {
        Angle = WrapMinMax(Angle, -M_PI, M_PI);
    }
}

void GameObject::Collided(GameObject& Other)
{
    for(int i = 0; i < (int)(_GameObjComponents.size()); i++)
    {
        _GameObjComponents[i]->Collided(Other);
    }
}

void GameObject::Render()
{
    for (int i = 0; i < (int)(_GameObjComponents.size()); i++)
    {
        _GameObjComponents[i]->Render();//Call render for each component belonging to this GameObject
    }
}

bool GameObject::IsDead()
{
    return _GameObjDead;
}

void GameObject::RequestDelete()
{
    _GameObjDead = true; //Sets object as ready for deletion
}

void GameObject::AddComponent(Component* GameComponent)
{
    _GameObjComponents.emplace_back(GameComponent); //Stores components belonging to current GameObject
}

void GameObject::RemoveComponent(Component* GameComponent)
{

    for (int i = 0; i < (int)(_GameObjComponents.size()); i++)
    {
        if(_GameObjComponents[i].get() == GameComponent)
        {
            _GameObjComponents.erase(_GameObjComponents.begin()+i); //Removal of an specific component identified by its pointer
            return;
        }
    }
}

Component* GameObject::GetComponent(std::string ComponentName)
{
    for (int i = 0; i < (int)(_GameObjComponents.size()); i++)
    {
        if(_GameObjComponents[i]->Is(ComponentName))
        {
            return _GameObjComponents[i].get(); //Get the pointer of the 1st component from a given type found on the Component array
        }
    }
    return nullptr; //Nothing has been found
}
