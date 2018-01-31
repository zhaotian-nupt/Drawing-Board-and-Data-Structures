#include "edge.h"

Edge::Edge(int vv,int ww)
{
    v=vv;
    w=ww;
}

void Edge::paint(QPainter &painter)
{
     painter.drawLine(start, end);

     double x1=start.x();
     double y1=start.y();
     double x2=end.x();
     double y2=end.y();
     double length=sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));

     double x3,x4,x5,y3,y4,y5;
     x3=31.0/30.0*(x2-x1)+x1;
     y3=31.0/30.0*(y2-y1)+y1;
     x4=x2+(y3-y2);
     y4=y2-(x3-x2);
     x5=x2-(y3-y2);
     y5=y2+(x3-x2);

     double temp1,temp2;
     temp1=x3-x2;
     temp2=y3-y2;
     x3-=temp1;
     x4-=temp1;
     x5-=temp1;
     y3-=temp2;
     y4-=temp2;
     y5-=temp2;

     QPoint p[4];
     p[1].setX(x3);
     p[1].setY(y3);
     p[2].setX(x4);
     p[2].setY(y4);
     p[3].setX(x5);
     p[3].setY(y5);

     painter.drawLine(p[1],p[2]);
     painter.drawLine(p[3],p[1]);

     int weightx=(x1+x2)/2;
     int weighty=(y1+y2)/2;
     QString qs = QString::number(W,10);
     painter.drawText(weightx,weighty+10,qs);
}

