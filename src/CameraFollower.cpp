#include "../lib/IncludeAll.hpp"

CameraFollower::CameraFollower(GameObject& GameObj)
: Component(GameObj)
{

}

void CameraFollower::Update(float Dt)
{
    GameObjAssoc.Box.x = Game::GetInstance().GetState().Cam.Position.x;
    GameObjAssoc.Box.y = Game::GetInstance().GetState().Cam.Position.y;
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