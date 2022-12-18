#include "../lib/IncludeAll.hpp"


Bullet::Bullet(GameObject& GameObj, float Angle, float Speed, int Damage, float MaxDistance, std::string Texture)
: Component(GameObj)
{

}

void Bullet::Update(float Dt)
{

}

void Bullet::Render()
{

}

bool Bullet::Is(std::string Type)
{
    return (Type == "Bullet");
}

void Bullet::Start()
{

}

int Bullet::GetDamage()
{
    return 0;
}