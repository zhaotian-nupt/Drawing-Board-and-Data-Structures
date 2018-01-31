#include "undiredge.h"

UndirEdge::UndirEdge(int uu,int vv,int ww)
{
    u=uu;
    v=vv;
    w=ww;
}
void UndirEdge::paint(QPainter &painter)
{
    painter.drawLine(start, end);
    int weightx=(start.x()+end.x())/2;
    int weighty=(start.y()+end.y())/2;
    QString qs = QString::number(W,10);
    painter.drawText(weightx,weighty+10,qs);
}
