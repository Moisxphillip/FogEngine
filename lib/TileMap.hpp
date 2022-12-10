#ifndef FOG_TILEMAP
#define FOG_TILEMAP

#include "../lib/IncludeAll.hpp"

class TileMap: public Component
{
    private:
        std::vector<int> _TileMatrix;
        TileSet *_CurrTileSet;
        int _MapWidth;
        int _MapHeight;
        int _LayerArea;
        int _MapDepth;
        int _RefLayer;
        float _GetLayerMult(int);

    public:
        TileMap(GameObject&, std::string, TileSet*);
        ~TileMap();
        void Load(std::string);
        void SetTileSet(TileSet*);
        int& At(int, int, int);        
        void RenderLayer(int, int, int);
        int GetWidth();
        int GetHeight();
        int GetDepth();

        void SetRefLayer(int);

        //inheritance functions
        void Render();
        void Update(float);
        bool Is(std::string);
    
};



#endif//FOG_TILEMAP