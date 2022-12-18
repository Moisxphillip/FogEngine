#include "../lib/IncludeAll.hpp"

Face::Face(GameObject& GameObj)
: Component(GameObj)
{
    _FaceHP = 5;
}

Face::~Face()
{
    
}


void Face::Damage(int Dmg)
{
    if(_SetToDie)//Avoids executing when the object should be dead
    {
        return;
    }

    _FaceHP-=Dmg;
    
    if(_FaceHP <= 0)
    {
        Sound *Explosion = (Sound*)(GameObjAssoc.GetComponent("Sound"));
        Explosion->Play(0);
        _SetToDie = true;
        GameObjAssoc.RemoveComponent(GameObjAssoc.GetComponent("Sprite"));
    }
}

void Face::Update(float Dt)
{
    if(_SetToDie)
    {
        Sound *Explosion = (Sound*)(GameObjAssoc.GetComponent("Sound"));
        if(!Explosion->IsPlaying())
        {
            GameObjAssoc.RequestDelete();
        }
    }
}

void Face::Render()
{
}

void Face::Start()
{
}

bool Face::Is(std::string Type)
{
    return Type == "Face";
}
