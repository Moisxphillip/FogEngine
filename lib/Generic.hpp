#ifndef FOG_GENERIC
#define FOG_GENERIC

#include "../lib/IncludeAll.hpp"

class Generic : public Component
{
    private:
        std::string _Type;
        void(*_Render)(Generic*);
        void(*_Start)(Generic*);
        void(*_Update)(float, Generic*);

    public:
        bool Started;

        //Argument holders
        std::map<std::string, int> Int;
        std::map<std::string, float> Float;
        std::map<std::string, bool> Bool;
        std::map<std::string, void*> Ptr;
        float& Angle;
        Rect& Box;


        Generic(GameObject&, std::string);
        void SetRender(void(*)(Generic*));
        void SetStart(void(*)(Generic*));
        void SetUpdate(void(*)(float, Generic*));
        void RequestDelete();
        
        bool Is(std::string);
        void Render();
        void Start();
        void Update(float);

};
//Use this class for short-lived and simple game objects. For now, only tests!

#endif//FOG_GENERIC
