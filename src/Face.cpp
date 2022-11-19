#include "../lib/IncludeAll.hpp"

Face::Face(GameObject& GameObj)
: Component(GameObj)
{
    _FaceHP = 20;
}

Face::~Face()
{
    
}


void Face::Damage(int Dmg)
{
    _FaceHP-=Dmg;
    if(_FaceHP <= 0)
    {
        Sound *Explosion = (Sound*)(GameObjAssoc.GetComponent("Sound"));
        Explosion->Play(1);
        
        GameObjAssoc.RequestDelete();
        //TODO Play sound of your associated, if there's any
    }
}

void Face::Update(float Dt)
{
}

void Face::Render()
{
}

bool Face::Is(std::string Type)
{
    return Type == "Face";
}
