#include "../lib/IncludeAll.hpp"

PenguinBody* PenguinBody::Player;

PenguinBody::PenguinBody(GameObject& GameObj)
: Component(GameObj)
{
    Player = this;
}

PenguinBody::~PenguinBody()
{

}


bool PenguinBody::Is(std::string Type)
{
    return ("PenguinBody" == Type);
}

void PenguinBody::Render()
{

}

void PenguinBody::Start()
{

}

void PenguinBody::Update(float Dt)
{

}
