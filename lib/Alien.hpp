#ifndef FOG_ALIEN
#define FOG_ALIEN

#include "../lib/IncludeAll.hpp"

class Alien : public Component
{
    private:
        class Action
        {
            public:
                Vec2 Position;
                enum ActionType
                {
                    MOVE,
                    SHOOT
                };        
                Action();
                Action(ActionType, float, float);
                Action(ActionType, Vec2);
                ActionType Type;
        };
        Vec2 _Speed;
        int _HP;
        int _NumMinions;
        Action _AlienAction;
        std::queue<Action> _AlienTasks;
        std::vector<std::weak_ptr<GameObject>> _MinionVec;

    public:
        Alien(GameObject&, int);
        ~Alien();
        
        bool Is(std::string);
        void Render();
        void Start();
        void Update(float);

};


#endif//FOG_ALIEN