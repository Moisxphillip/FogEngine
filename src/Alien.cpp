#include "../lib/IncludeAll.hpp"


Alien::Alien(GameObject& GameObj, int NumMinions)
: Component(GameObj)
{
    _HP = 100;
    _NumMinions = NumMinions;
    _Speed = Vec2(100,100);
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
    _MinionVec.reserve(_NumMinions);
    for(int i = 0; i< _NumMinions; i++)
    {
        GameObject* MinionObj = new GameObject;
        Minion* NewMinion = new Minion(*MinionObj, Game::GetInstance().GetState().GetGameObjPtr(&GameObjAssoc),(2.0f* M_PI * i)/_NumMinions);
        MinionObj->AddComponent(NewMinion);
        _MinionVec.push_back(Game::GetInstance().GetState().AddGameObj(MinionObj));
    }
    //Do nothing until alien works properly
}

void Alien::Update(float Dt)
{
    //Alien Rotation
    GameObjAssoc.Angle += (ROTFRAC/2)*Dt;


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

        Vec2 Distance = GameObjAssoc.Box.Center() - _AlienTasks.front().Position;
        if(_AlienTasks.front().Type == Action::MOVE)
        {
            Vec2 Direction = Distance.Normalized();
            Direction.x *= _Speed.x * Dt;
            Direction.y *= _Speed.y * Dt;
            GameObjAssoc.Box -= Direction;
            if(Direction.Magnitude() >= Distance.Magnitude())
            {
                GameObjAssoc.Box += Distance;
                _AlienTasks.pop();
            }
            //
            
        }
        else if (_AlienTasks.front().Type == Action::SHOOT)
        {
            float Closest = 1e7; //A big number for quick substitution
            int Index = 0;

            for(int i = 0; i < _NumMinions; i++)
            {
                //Gets the center of a minion, then the distance between it and the clicked point
                float Dist = _MinionVec[i].lock()->Box.Center().Distance(_AlienTasks.front().Position);
                if(Dist < Closest)
                {
                    Closest = Dist;
                    Index = i;
                }
            }
            Minion* ChosenToShoot = (Minion*) _MinionVec[Index].lock()->GetComponent("Minion");
            ChosenToShoot->Shoot(_AlienTasks.front().Position);
            _AlienTasks.pop();
        }
    }

    if(_HP == 0)
    {
        for(int i = 0; i < _NumMinions; i++)
        {
            _MinionVec[i].lock()->RequestDelete(); //Request delete for minions
        }
        GameObjAssoc.RequestDelete(); //Request delete for alien
    }
}

void Alien::Render()
{
}

bool Alien::Is(std::string Type)
{
    return (Type == "Alien");
}
