#include "../lib/IncludeAll.hpp"

Collider::Collider(GameObject& GameObj, Vec2 Scale, Vec2 Offset)
: Component(GameObj)
{
    _Scale = Scale;
    _Offset = Offset;
}

Collider::Collider(GameObject& GameObj)
: Collider(GameObj, Vec2(1,1), Vec2(0,0))
{
}

void Collider::SetScale(Vec2 NewScale)
{
    _Scale = NewScale;
}
void Collider::SetOffset(Vec2 NewOffset)
{
    _Offset = NewOffset;
}

bool Collider::Is(std::string Type)
{
    return ("Collider" == Type);
}

void Collider::Render() 
{
#ifdef DEBUG
	Vec2 Center = Box.Center();
	SDL_Point SDLPoints[5];

	Vec2 Point = (Vec2(Box.x, Box.y) - Center).Rotate(Vec2::RadToDeg(GameObjAssoc.Angle))
					+ Center - Game::GetInstance().GetState().Cam.Position;
	SDLPoints[0] = {(int)Point.x, (int)Point.y};
	SDLPoints[4] = {(int)Point.x, (int)Point.y};
	
	Point = (Vec2(Box.x + Box.w, Box.y) - Center).Rotate(Vec2::RadToDeg(GameObjAssoc.Angle))
					+ Center - Game::GetInstance().GetState().Cam.Position;
	SDLPoints[1] = {(int)Point.x, (int)Point.y};
	
	Point = (Vec2(Box.x + Box.w, Box.y + Box.h) - Center).Rotate(Vec2::RadToDeg(GameObjAssoc.Angle))
					+ Center - Game::GetInstance().GetState().Cam.Position;
	SDLPoints[2] = {(int)Point.x, (int)Point.y};
	
	Point = (Vec2(Box.x, Box.y + Box.h) - Center).Rotate(Vec2::RadToDeg(GameObjAssoc.Angle))
					+ Center - Game::GetInstance().GetState().Cam.Position;
	SDLPoints[3] = {(int)Point.x, (int)Point.y};

	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), SDLPoints, 5);
#endif //_DEBUG
}

void Collider::Start()
{
    
}

void Collider::Update(float Dt)
{
    
}