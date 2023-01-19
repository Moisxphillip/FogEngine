#include "../lib/IncludeAll.hpp"

SpriteGL::SpriteGL(GameObject& GameObj)
: Component(GameObj)
{
    ComponentFlags = Uses::Render | Uses::Update;
    _SpriteTexture = nullptr;
    _Scale = Vec2(1,1);
    _FrameCount = 0;
    _CurrFrame = 0;
    _TimeElapsed = 0;
    _FrameTime = 0;
    _Orientation = Flip::N;
    Loop = true;
    LifeTime = 0;
    ToSelfDestruct.Restart();

    _VboID = 0;
}

SpriteGL::SpriteGL(GameObject& GameObj, std::string File)
: SpriteGL(GameObj)
{
    Open(File);
}

SpriteGL::SpriteGL(GameObject& GameObj, std::string File, int FrameCount = 1, float FrameTime = 1)
: SpriteGL(GameObj)
{
    Open(File);
    _FrameCount = FrameCount;
    _FrameTime = FrameTime;
    _SpriteWidth /= FrameCount;
    SetClip(0,0, _SpriteWidth, _SpriteHeight);    
}

SpriteGL::SpriteGL(GameObject& GameObj, std::string File, int FrameCount = 1, float FrameTime = 1, float LifeTime = 0)
: SpriteGL(GameObj)
{
    Open(File);
    _FrameCount = FrameCount;
    _FrameTime = FrameTime;
    _SpriteWidth /= FrameCount;
    SetClip(0,0, _SpriteWidth, _SpriteHeight);
    this->LifeTime = LifeTime;
}

SpriteGL::~SpriteGL()
{
    if(_VboID != 0)
    {
        glDeleteBuffers(1, &_VboID);
    }
}

void SpriteGL::Init(float x, float y, float w, float h)
{
    GameObjAssoc.Box.x = x;
    GameObjAssoc.Box.y = y;
    GameObjAssoc.Box.w = w;
    GameObjAssoc.Box.h = h;
    if(_VboID == 0)
    {
        glGenBuffers(1, &_VboID);
    }
    Vertex VertexData[6];
    VertexData[0].SetPos(x+w, y+h);
    VertexData[1].SetPos(x, y+h);
    VertexData[2].SetPos(x, y);
    
    //second triangle
    VertexData[3].SetPos(x, y);
    VertexData[4].SetPos(x+w, y);
    VertexData[5].SetPos(x+w, y+h);

    VertexData[0].SetUV(1,1);
    VertexData[1].SetUV(0,1);
    VertexData[2].SetUV(0,0);
    VertexData[3].SetUV(0,0);
    VertexData[4].SetUV(1,0);
    VertexData[5].SetUV(1,1);

    for(int i = 0; i<6; i++)
    {
        VertexData[i].SetColors(255, 127, 0, 255);
    }

    glBindBuffer(GL_ARRAY_BUFFER, _VboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData), VertexData, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SpriteGL::Open(std::string File)
{
    _SpriteTexture = Resources::GetImage(File);
    if(_SpriteTexture == nullptr)
    {
        Error("SpriteGL::Open: Image could not be loaded");
    }

    if(SDL_QueryTexture(_SpriteTexture, nullptr, nullptr, &_SpriteWidth, &_SpriteHeight))
    {
        Error("SpriteGL::Open: QueryTexture failed");
    }
    SetClip(0,0, _SpriteWidth, _SpriteHeight);
}

void SpriteGL::SetClip(int x, int y, int w, int h)
{
    _ClipRect.x = x;
    _ClipRect.y = y;
    _ClipRect.w = w;
    _ClipRect.h = h;
}


int SpriteGL::GetWidth()
{
    return (_SpriteWidth * _Scale.x);
}

int SpriteGL::GetHeight()
{
    return (_SpriteHeight * _Scale.y);
}

void SpriteGL::SetScale(float ScaleX, float ScaleY)
{
    _Scale = Vec2(ScaleX, ScaleY);
}

Vec2 SpriteGL::GetScale()
{
    return _Scale;
}

bool SpriteGL::IsOpen()
{
    return (_SpriteTexture != nullptr);
}

void SpriteGL::SetFrame(int Frame)
{
    _CurrFrame = Frame;
    SetClip(_CurrFrame*_SpriteWidth, 0, _SpriteWidth, _SpriteHeight);
}

void SpriteGL::SetFrameCount(int FrameCount)
{
    _FrameCount = FrameCount;
}

void SpriteGL::SetFrameTime(float FrameTime)
{
    _FrameTime = FrameTime;
}

void SpriteGL::SetFlip(Flip Direction)
{
    _Orientation = Direction;
}

Flip SpriteGL::GetFlip()
{
    return _Orientation;
}


//Inheritance
bool SpriteGL::Is(std::string Type)
{
    return ("Sprite" == Type);
}

void SpriteGL::Render()
{
    glBindBuffer(GL_ARRAY_BUFFER, _VboID);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Pos));
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, Colors));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Uv));
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    //Render(GameObjAssoc.Box.x, GameObjAssoc.Box.y);
}

void SpriteGL::Render(float x, float y)
{
    Render(x, y, GameObjAssoc.Angle);
}

void SpriteGL::Render(float x, float y, float Angle)
{
    SDL_Rect DestinyRect;
    DestinyRect.x = x - Game::GetInstance().GetState().Cam.Position.x;
    DestinyRect.y = y - Game::GetInstance().GetState().Cam.Position.y;
    DestinyRect.w = _ClipRect.w  * _Scale.x;
    DestinyRect.h = _ClipRect.h * _Scale.y;

    if(SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), _SpriteTexture, &_ClipRect, &DestinyRect, Vec2::RadToDeg(Angle), nullptr, (SDL_RendererFlip) _Orientation))
    {
        Error("SpriteGL::Render: Sprite copy to render device has failed");
    }
}

void SpriteGL::Start()
{
}

void SpriteGL::Update(float Dt)
{
    // if(LifeTime > 0)
    // {
    //     ToSelfDestruct.Update(Dt);
    //     if(ToSelfDestruct.Get() >= LifeTime)
    //     {
    //         GameObjAssoc.RequestDelete();
    //     }
    // }

    // _TimeElapsed += Dt;
    // if(_TimeElapsed >= _FrameTime && _FrameCount > 1)
    // {
        
    //     if(Loop == true || _CurrFrame < _FrameCount-1)
    //     {
    //         ++_CurrFrame%=_FrameCount;
    //         SetFrame(_CurrFrame);
    //     }
            
    //     _TimeElapsed = 0;
    // }
}


