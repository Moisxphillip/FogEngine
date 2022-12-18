#include "../lib/IncludeAll.hpp"


Alien::Alien(GameObject& GameObj, int NumMinions)
: Component(GameObj)
{
    _HP = 0;
    _MinionVec.reserve(NumMinions);
    _Speed = Vec2(20,20);

    Sprite *SpriteAlien = new Sprite(GameObj, FIMG_ALIEN);
    GameObjAssoc.Box.h = SpriteAlien->GetHeight();
    GameObjAssoc.Box.w = SpriteAlien->GetWidth();
    GameObjAssoc.AddComponent(SpriteAlien);
}

Alien::~Alien()
{

}

Alien::Action::Action()
{
}

Alien::Action::Action(ActionType Type, float x, float y)
{
    this->Type = Type;
    Position = Vec2(x,y);
}

Alien::Action::Action(ActionType Type, Vec2 Coord)
{
    this->Type = Type;
    Position = Coord;
}

void Alien::Start()
{
    //Do nothing until alien works properly
}

void Alien::Update(float Dt)
{
    if(InputManager::GetInstance().MousePress(M_LEFT))
    {
        Action NewAction(Action::SHOOT, InputManager::GetInstance().GetMouseX(),
            InputManager::GetInstance().GetMouseY());
        _AlienTasks.emplace(NewAction);
    }
    
    if(InputManager::GetInstance().MousePress(M_RIGHT))
    {
        Action NewAction(Action::MOVE, InputManager::GetInstance().GetMouseX(),
            InputManager::GetInstance().GetMouseY());
        _AlienTasks.emplace(NewAction);
    }

    if(!_AlienTasks.empty())
    {
        Action Curr = _AlienTasks.front();
        Vec2 Distance = GameObjAssoc.Box.Center() - Curr.Position;
        if(Curr.Type == Action::MOVE)
        {
            if(_Speed.Magnitude()*Dt >= Distance.Magnitude()*Dt)
            {
                GameObjAssoc.Box.x += _Speed.x* Dt;
                GameObjAssoc.Box.y += _Speed.y* Dt;
                _AlienTasks.pop();
            }

            //_Speed.Rotate(-(_Speed.Angle()-Distance.Angle()));

            GameObjAssoc.Box.x += _Speed.x* Dt;
            GameObjAssoc.Box.y += _Speed.y* Dt;
        }
        else if (Curr.Type == Action::SHOOT)
        {
            std::cout << "Pew\n";
            _AlienTasks.pop();
        }
    }
}

void Alien::Render()
{
}

bool Alien::Is(std::string Type)
{
    return (Type == "Alien");
}
