#include "point.h"
#include "cstdio"
#include "data.h"
extern Data graph_data;

Point::Point()
{
    x1=x2=y1=y2=r=0;
    xx=yy=0;
    isroot=false;
    level=1;
}

void Point::paint(QPainter &painter)
{
    painter.drawEllipse(start.x(),start.y(),end.x()-start.x(),end.y()-start.y());
    QString qs = QString::number(id,10);
    int x=graph_data.p[id].xx-3;
    int y=graph_data.p[id].yy+3;
    painter.drawText(x,y,qs);
}

void Point::update_r()
{
    r=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))/2.0;
    xx=(x1+x2)/2.0;
    yy=(y1+y2)/2.0;
}
