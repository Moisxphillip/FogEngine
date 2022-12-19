#include "../lib/IncludeAll.hpp"

#define ROTFRAC (M_PI/4)

Minion::Minion(GameObject& GameObj, std::weak_ptr<GameObject> AlienCenter, float Arc)
: Component(GameObj), _AlienCenter(AlienCenter)
{
    _Arc = Arc;
    Sprite* Mini = new Sprite(GameObj,FIMG_MINION);
    GameObjAssoc.Box.h = Mini->GetHeight();
    GameObjAssoc.Box.w = Mini->GetWidth();
    GameObjAssoc.AddComponent(Mini);
}

void Shoot(Vec2 Target)
{

}

bool Minion::Is(std::string Type)
{
    return (Type == "Minion");
}

void Minion::Render()
{
}

void Minion::Start()
{

}

void Minion::Update(float Dt)
{
    if(!_AlienCenter.expired())
    {
        std::shared_ptr<GameObject> CurrCenter = _AlienCenter.lock();
        Vec2 DistToCenter(200,0);
        _Arc += ROTFRAC*Dt;
        DistToCenter.Rotate(_Arc);
        GameObjAssoc.Box.SetCenter(DistToCenter + CurrCenter->Box.Center());
    }
    else
    {
        GameObjAssoc.RequestDelete();
    }
}
