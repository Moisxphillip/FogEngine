#ifndef FOG_FACE
#define FOG_FACE

#include "../lib/IncludeAll.hpp"

class Face : public Component
{
    private:
        int _FaceHP;
        bool _SetToDie = false;

    public:
        Face(GameObject&);
        ~Face();

        void Damage(int);
        bool Is(std::string);
        void Render();
        void Start();
        void Update(float);

};



#endif//FOG_FACE