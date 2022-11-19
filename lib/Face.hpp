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
        
        void Update(float);
        void Render();
        bool Is(std::string);

};



#endif//FOG_FACE