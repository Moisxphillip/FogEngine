#ifndef FOG_RECT
#define FOG_RECT

class Rect
{
    public:
        int x, y, w, h;

    Rect(int, int, int, int);
    Rect();


    bool IsInside(const int&, const int&);
    

};



#endif//FOG_RECT