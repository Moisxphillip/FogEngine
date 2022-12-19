#include "../lib/IncludeAll.hpp"

#define SPDMAX 300
        
Camera::Camera()
{
    _Focus = nullptr;
    Position = Vec2(0,0);
    Speed = Vec2(0, 0);
}

void Camera::Follow(GameObject* Focus)
{
    _Focus = Focus;
    Position = _Focus->Box.Center() - Vec2(FOG_SCRWIDTH>>1, FOG_SCRHEIGHT>>1);
}

void Camera::Unfollow()
{
    _Focus = nullptr;
    Speed = Vec2(0,0);
}

bool Camera::IsFollowing()
{
    return (_Focus != nullptr);
}

void Camera::Update(float Dt)
{
    if(_Focus != nullptr)
    {
        Position  = _Focus->Box.Center() - Vec2(FOG_SCRWIDTH>>1, FOG_SCRHEIGHT>>1);//focus on the given object
    }
    else
    {
        Speed.y += ((InputManager::GetInstance().IsKeyDown(K_S) | InputManager::GetInstance().IsKeyDown(K_DOWNARROW)) 
        - (InputManager::GetInstance().IsKeyDown(K_W)| InputManager::GetInstance().IsKeyDown(K_UPARROW)))* Dt * 100;
        Speed.x += ((InputManager::GetInstance().IsKeyDown(K_D) | InputManager::GetInstance().IsKeyDown(K_RIGHTARROW))
        - (InputManager::GetInstance().IsKeyDown(K_A)| InputManager::GetInstance().IsKeyDown(K_LEFTARROW)))* Dt * 100;
        
        (InputManager::GetInstance().KeyPress(K_B) ? Speed = Vec2(0,0):Speed);
        Position+= Speed*Dt;

        //Speed limiters
        (Speed.x > SPDMAX ? Speed.x = SPDMAX:0);
        (Speed.x < -SPDMAX ? Speed.x = -SPDMAX:0);
        (Speed.y > SPDMAX ? Speed.y = SPDMAX:0);
        (Speed.y < -SPDMAX ? Speed.y = -SPDMAX:0);
    }
}