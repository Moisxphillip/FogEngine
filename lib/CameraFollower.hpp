#ifndef FOG_CAMFOLLOW
#define FOG_CAMFOLLOW

#include "../lib/IncludeAll.hpp"

class CameraFollower: public Component
{
    private:

    public:
        CameraFollower(GameObject&);
        void Update(float);
        void Render();
        bool Is();

};


#endif//FOG_CAMFOLLOW