#ifndef FOG_FACE
#define FOG_FACE

#include "../lib/Component.hpp"

class Face : public Component
{
    private:
        int _FaceHP;

    public:
        Face(GameObject&);
        void Damage(int);
        void Update(float);
        void Render();
        bool Is(std::string);

};



#endif//FOG_FACE