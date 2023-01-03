#include "../lib/IncludeAll.hpp"

PenguinBody* PenguinBody::Player;

PenguinBody::PenguinBody(GameObject& GameObj)
: Component(GameObj)
{
    Player = this;
    _Speed = Vec2(0,0);
    _HP = 100;
    GameObjAssoc.Angle = 0;
    _LinearSpeed = 0;
    Sprite* Body = new Sprite(GameObj, FIMG_PENGBODY);
    GameObjAssoc.Box = Rect(0,0, Body->GetWidth(), Body->GetHeight());
    Collider* CollidePenguin = new Collider(GameObj);
	CollidePenguin->Box = GameObjAssoc.Box;
    GameObjAssoc.AddComponent(Body);
    GameObjAssoc.AddComponent(CollidePenguin);

}

PenguinBody::~PenguinBody()
{
    Player = nullptr;
}

Vec2 PenguinBody::CurrPosition()
{
    return GameObjAssoc.Box.Center();
}

void PenguinBody::Collided(GameObject& Other)
{
    Bullet* Shot = (Bullet*) Other.GetComponent("Bullet");
    if(Shot != nullptr)
    {
        if (Shot->TargetsPlayer)
        {
            _HP -= Shot->GetDamage();
            Other.RequestDelete();
            if(_HP<=0)
            {
                Game::GetInstance().GetState().Cam.Unfollow();
            }
        }
    }
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
    GameObject* Cannon = new GameObject();
    PenguinCannon* CannonCub = new PenguinCannon(*Cannon, Game::GetInstance().GetState().GetGameObjPtr(&GameObjAssoc));
    Cannon->AddComponent(CannonCub);
    Game::GetInstance().GetState().AddGameObj(Cannon);
}

void PenguinBody::Update(float Dt)
{
    GameObjAssoc.Angle+= (InputManager::GetInstance().IsKeyDown(K_D)-InputManager::GetInstance().IsKeyDown(K_A))
    * Dt * M_PI;
    _LinearSpeed+= (InputManager::GetInstance().IsKeyDown(K_S)-InputManager::GetInstance().IsKeyDown(K_W)) 
    * Dt * FOG_PENGACCEL;

    if(_LinearSpeed > FOG_PENGSPDMAX)
    {
        _LinearSpeed = FOG_PENGSPDMAX;
    }
    else if (_LinearSpeed < -FOG_PENGSPDMAX)
    {
        _LinearSpeed = -FOG_PENGSPDMAX;
    }

    Vec2 Move(_LinearSpeed*Dt, 0);
    Move.Rotate(GameObjAssoc.Angle);
    GameObjAssoc.Box-=Move;


    if(_HP<=0)
    {
        GameObject* Death = new GameObject();
        Sprite* PengDeath = new Sprite(*Death, FIMG_PENGDEATH, 5, FOG_DEATHFRAMETIME, 1);
        PengDeath->Loop = false;
        Death->Box.h = PengDeath->GetHeight();
        Death->Box.w = PengDeath->GetWidth();
        Death->Box.SetCenter(GameObjAssoc.Box.Center());
        Death->AddComponent(PengDeath);
        Game::GetInstance().GetState().AddGameObj(Death);

        GameObject* DeathSound = new GameObject();
        DeathSound->Box = Death->Box;
        Sound* Boom = new Sound(*DeathSound, FAUD_BOOM);
        Boom->Pan = true;
        Boom->SelfDestruct = true; 
        Boom->Play(0);
        DeathSound->AddComponent(Boom);
        Game::GetInstance().GetState().AddGameObj(DeathSound);

        GameObjAssoc.RequestDelete();
    }
}
