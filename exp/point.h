#ifndef RECT_H
#define RECT_H

#include "shape.h"

class Point : public Shape
{
public:
        Point();
        void paint(QPainter &painter);
        double x1,x2,y1,y2;
        double xx,yy;
        double r;
        bool isroot;
        int level;
        void update_r();
        double getlength(QPoint qp)
        {
            return sqrt((qp.x()-xx)*(qp.x()-xx)+(qp.y()-yy)*(qp.y()-yy));
        }
};

#endif // RECT_H
