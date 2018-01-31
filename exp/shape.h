#ifndef SHAPE_H
#define SHAPE_H

#include <QtWidgets>

class Shape
{
public:
        enum Code {
                Edge,
                UndirEdge,
                Point,
                Finish,
                Bianli,
                MST,
                SP
        };

        Shape();

        void setStart(QPoint s)
        {
                start = s;
        }

        void setEnd(QPoint e)
        {
                end = e;
        }

        QPoint startPoint()
        {
                return start;
        }

        QPoint endPoint()
        {
                return end;
        }

        void addPoint()
        {

        }

        void virtual paint(QPainter & painter) = 0;

public:
        QPoint start;
        QPoint end;
        int id;
        int W;
};


#endif // SHAPE_H
