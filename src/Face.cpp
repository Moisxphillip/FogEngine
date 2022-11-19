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
    if(_FaceHP <= 0)//Avoids executing the sound twice
    {
        return;
    }

    _FaceHP-=Dmg;
    
    if(_FaceHP <= 0)
    {
        Sound *Explosion = (Sound*)(GameObjAssoc.GetComponent("Sound"));
        Explosion->Play(1);
        GameObjAssoc.RemoveComponent(GameObjAssoc.GetComponent("Sprite"));
        _SetToDie = true;//Gambiarra do som
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

bool Face::Is(std::string Type)
{
    return Type == "Face";
}
