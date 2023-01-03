#include "../lib/IncludeAll.hpp"


PenguinCannon::PenguinCannon(GameObject& GameObj, std::weak_ptr<GameObject> Body)
: Component(GameObj)
{   
    GameObjAssoc.Angle = 0;
    Sprite* Cannon = new Sprite(GameObj, FIMG_PENGGUN);
    Cannon->SetScale(0.8,0.8);
    GameObjAssoc.Box = Rect(0,0,Cannon->GetWidth(),Cannon->GetHeight());
    _Body = Body;
    GameObjAssoc.Box.SetCenter(_Body.lock()->Box.Center());
    Collider* CollideCannon = new Collider(GameObj);
	CollideCannon->Box = GameObjAssoc.Box;
    GameObjAssoc.AddComponent(Cannon);
    GameObjAssoc.AddComponent(CollideCannon);
    _Cooldown.Restart();
}

void PenguinCannon::Shoot()
{
    float Angle = GameObjAssoc.Box.Center().DistAngle(InputManager::GetInstance().GetMouseVec2());
    Vec2 ExtraDistance(50,0);
    ExtraDistance.Rotate(Angle);
    GameObject* GoBullet= new GameObject;
    Bullet* Projectile = new Bullet(*GoBullet, Angle, FOG_BULLETSPD,
             FOG_BULLETDMG, FOG_BULLETDIST, FIMG_PENGBULLET, 4, false, false);
    GoBullet->Box.SetCenter(GameObjAssoc.Box.Center());
    GoBullet->Box+=ExtraDistance;
    GoBullet->AddComponent(Projectile);
    Game::GetInstance().GetState().AddGameObj(GoBullet);
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
    _Cooldown.Update(Dt);
    if(!_Body.expired())
    {
        GameObjAssoc.Box.SetCenter(_Body.lock()->Box.Center());
        GameObjAssoc.Angle = GameObjAssoc.Box.Center().DistAngle(InputManager::GetInstance().GetMouseVec2());
        if(InputManager::GetInstance().MousePress(M_LEFT) && _Cooldown.Get() > 1.8)
        {
            Shoot();
            _Cooldown.Restart();
        }
    }
    else
    {
        GameObjAssoc.RequestDelete();
    }
}
