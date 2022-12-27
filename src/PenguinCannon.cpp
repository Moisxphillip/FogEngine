#include "../lib/IncludeAll.hpp"


PenguinCannon::PenguinCannon(GameObject& GameObj, std::weak_ptr<GameObject> Body)
: Component(GameObj)
{

}

void PenguinCannon::Shoot()
{

}

bool PenguinCannon::Is(std::string Type)
{
    return ("PenguinCannon" == Type);
}

void PenguinCannon::Render()
{

}

void PenguinCannon::Start()
{

}

void PenguinCannon::Update(float Dt)
{

}
