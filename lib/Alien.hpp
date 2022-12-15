#ifndef FOG_ALIEN
#define FOG_ALIEN

#include "../lib/IncludeAll.hpp"

class Alien : public GameObject
{
    private:
        //Action _AlienAction;
        Vec2 _Speed;
        int _HP;
        //std::queue<Action> _AlienTasks;
        std::vector<std::weak_ptr<GameObject>> _MinionVec;

    public:
        Alien();
        ~Alien();
        void Start();
        void Update(float);
        void Render();
        bool Is(std::string);

};


#endif//FOG_ALIEN