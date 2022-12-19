#include "../lib/IncludeAll.hpp"

Generic::Generic(GameObject& GameObj, std::string Type)
: Component(GameObj)
{
    _Type = Type;
    this->Started = false;
    _Render = nullptr;
    _Start = nullptr;
    _Update = nullptr;
}

void Generic::SetRender(void(*Render)(Generic*))
{
    _Render = Render;
}

void Generic::SetStart(void(*Start)(Generic*))
{
    _Start = Start;
}

void Generic::SetUpdate(void(*Update)(float, Generic*))
{
    _Update = Update;
}

bool Generic::Is(std::string Type)
{
    return (Type == _Type);
}

void Generic::Render()
{
    if(_Render != nullptr)
    {
        _Render(this);
    }
}

void Generic::Start()
{
    if(_Start != nullptr)
    {
        _Start(this);
        this->Started = true;
    }
}

void Generic::Update(float Dt)
{
    if(_Update != nullptr)
    {
        _Update(Dt, this);
    }
}

