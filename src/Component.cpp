#include "../lib/IncludeAll.hpp"



Component::Component(GameObject& GameObj)
: GameObjAssoc(GameObj)
{
}

Component::~Component()
{
}

void Component::Render()
{
}

void Component::Update(float Dt)
{
}

bool Component::Is(std::string Type)
{
}