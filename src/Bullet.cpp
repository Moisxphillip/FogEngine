#include "../lib/IncludeAll.hpp"


Bullet::Bullet(GameObject& GameObj, float Angle, float Speed, int Damage, float MaxDistance, std::string Texture)
: Component(GameObj)
{
    Sprite* SpBullet = new Sprite(GameObj, Texture);
    GameObjAssoc.AddComponent(SpBullet);
    GameObjAssoc.Box.h = SpBullet->GetHeight();
    GameObjAssoc.Box.w = SpBullet->GetWidth();
    
    _Speed = Vec2(1,0)*Speed;
    _Speed.Rotate(Angle);
    _DistanceLeft = MaxDistance;
    
    _Damage = Damage;

}

bool Bullet::Is(std::string Type)
{
    return (Type == "Bullet");
}

void Bullet::Render()
{
}

void Bullet::Start()
{
}

void Bullet::Update(float Dt)
{
    GameObjAssoc.Box.x += _Speed.x*Dt;
    GameObjAssoc.Box.y -= _Speed.y*Dt;
    _DistanceLeft -= _Speed.Magnitude()*Dt;
    if(_DistanceLeft <= 0)
    {
        GameObjAssoc.RequestDelete();
    }

}

int Bullet::GetDamage()
{
    return _Damage;
}