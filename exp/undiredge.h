#ifndef UNDIREDGE_H
#define UNDIREDGE_H
#include "shape.h"

class UndirEdge : public Shape
{
public:
    UndirEdge(int uu=0,int vv=0,int ww=0);
    void paint(QPainter &painter);
    int u;
    int v;
    int w;
    bool operator <(const UndirEdge &e)const
    {
        return e.w>w;
    }
};

#endif // UNDIREDGE_H
