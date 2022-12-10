#include "../lib/IncludeAll.hpp"

#define SPDMAX 10
#define SPDMIN 0.3
        
Camera::Camera()
{
    _Focus = nullptr;
    Position = Vec2(0,0);
    Speed = Vec2(0, 0);
}

inline void Camera::Follow(GameObject* Focus)
{
    _Focus = Focus;
    Position = _Focus->Box.Center();
}

inline void Camera::Unfollow()
{
    _Focus = nullptr;
}

void Camera::Update(float Dt)
{
    if(_Focus != nullptr)
    {
        Position  = _Focus->Box.Center();//focus on the given object
    }
    else
    {
        Speed.y += ((InputManager::GetInstance().IsKeyDown(K_S) | InputManager::GetInstance().IsKeyDown(K_DOWNARROW)) 
        - (InputManager::GetInstance().IsKeyDown(K_W)| InputManager::GetInstance().IsKeyDown(K_UPARROW)))* Dt * 10;
        Speed.x += ((InputManager::GetInstance().IsKeyDown(K_D) | InputManager::GetInstance().IsKeyDown(K_RIGHTARROW))
        - (InputManager::GetInstance().IsKeyDown(K_A)| InputManager::GetInstance().IsKeyDown(K_LEFTARROW)))* Dt * 10;

        //Speed limiters
        (Speed.x > SPDMAX ? Speed.x = SPDMAX:0);
        (Speed.x < -SPDMAX ? Speed.x = -SPDMAX:0);
        (Speed.y > SPDMAX ? Speed.y = SPDMAX:0);
        (Speed.y < -SPDMAX ? Speed.y = -SPDMAX:0);
        (abs(Speed.x) < SPDMIN ? Speed.x = 0:0);
        (abs(Speed.y) < SPDMIN ? Speed.y = 0:0);
    }
}