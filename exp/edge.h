#ifndef LINE_H
#define LINE_H

#include "shape.h"

class Edge : public Shape
{
public:
        Edge(int vv=0,int ww=0);
        void paint(QPainter &painter);
        int v,w;
};

#endif // LINE_H
