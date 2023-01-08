#include "../lib/IncludeAll.hpp"

CameraFollower::CameraFollower(GameObject& GameObj)
: Component(GameObj)
{
    Offset = Vec2(0,0);
}

void CameraFollower::Update(float Dt)
{
    GameObjAssoc.Box.x = Game::GetInstance().GetState().Cam.Position.x + Offset.x;
    GameObjAssoc.Box.y = Game::GetInstance().GetState().Cam.Position.y + Offset.y;
}

void CameraFollower::Render()
{
}

void CameraFollower::Start()
{
}

bool CameraFollower::Is(std::string Type)
{
    return (Type == "CameraFollower");
}