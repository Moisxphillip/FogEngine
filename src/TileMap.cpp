#include "../lib/IncludeAll.hpp"

TileMap::TileMap(GameObject& GameObj, std::string File, TileSet* CurrTileSet)
: Component(GameObj)
{
    _CurrTileSet = nullptr;
    this->Load(File);
    this->SetTileSet(CurrTileSet);
    
}

TileMap::~TileMap()
{
    delete _CurrTileSet;
    _CurrTileSet = nullptr;
}

void TileMap::Load(std::string File)
{
    std::ifstream TextMap(File);
    if(!TextMap.is_open())
    {
        Error("TileMap::Load: File could not be opened");
        return;
    }
    std::string Entry;//Will collect the inputs for interpretation and storage
    
    //gets initial info about the map file
    std::getline(TextMap, Entry, ',');
    _MapWidth = stoi(Entry);
    std::getline(TextMap, Entry, ',');
    _MapHeight = stoi(Entry);
    std::getline(TextMap, Entry, ',');
    _MapDepth = stoi(Entry);
    
    _LayerArea = _MapHeight*_MapWidth;
    int TotalSize = _LayerArea*_MapDepth;

    _TileMatrix.reserve(TotalSize);//reserving beforehand to avoid losing performance with memory resizing
    for(int i = 0; i<TotalSize; i++)//gets sprite indexes for all layers
    {
        std::getline(TextMap, File, ',');
        _TileMatrix.push_back(stoi(File));
    }

    TextMap.close();
}

void TileMap::SetTileSet(TileSet* ToBeSet)
{
    if(ToBeSet == nullptr)
    {
        Error("TileMap::SetTileSet: New TileSet is null");
    }
    else if(_CurrTileSet != nullptr)
    {
        delete _CurrTileSet;
        _CurrTileSet = nullptr;
    }

    _CurrTileSet = ToBeSet;
}

int& TileMap::At(int x, int y, int z = 0)
{
    return _TileMatrix[(x + _MapWidth*y)+ _LayerArea*z];
}

void TileMap::Render()
{
    for(int l = 0; l<_MapDepth; l++)//Renders each layer separately
    {
        RenderLayer(l, GameObjAssoc.Box.x, GameObjAssoc.Box.y);//Following specification hint
    }
}

void TileMap::RenderLayer(int Layer, int CamX, int CamY)
{
    for(int y = 0; y < _MapHeight; y++)//iterates through rows
    {
        for(int x = 0; x < _MapWidth; x++)//iterates through columns
        {
            _CurrTileSet->RenderTile(At(x, y, Layer), //finds tile identifier
                float(x*_CurrTileSet->GetTileWidth()), //dimensions to crop
                float(y*_CurrTileSet->GetTileHeight()));
        }        
    }
}

int TileMap::GetWidth()
{
    return _MapWidth;
}

int TileMap::GetHeight()
{
    return _MapHeight;
}

int TileMap::GetDepth()
{
    return _MapDepth;
}

void TileMap::Update(float Dt)
{
}

bool TileMap::Is(std::string Type)
{
    return (Type == "TileMap");
}