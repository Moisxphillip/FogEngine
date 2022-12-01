#ifndef FOG_CAMERA
#define FOG_CAMERA

#include "../lib/IncludeAll.hpp"

class Camera
{
    private:
        GameObject* _Focus;

    public:
        Vec2 Position;
        Vec2 Speed;
        
        Camera();
        
        void Follow(GameObject*);
        void Unfollow();
        void Update(float);

};

#endif//FOG_CAMERA