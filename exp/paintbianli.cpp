#include "paintbianli.h"

extern Data graph_data;

PaintBianli::PaintBianli(QWidget *parent)
{

}

void PaintBianli::Bianli()
{

}

void PaintBianli::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    painter.setBrush(Qt::white);
    painter.setPen(QColor(0, 0, 0));
    painter.drawRect(0, 0, size().width(), size().height());

    QPen pen;
    pen.setWidth(2);
    painter.setPen(pen);

    QFont font;
    font.setPointSize(10);
    font.setBold(true);
    painter.setFont(font);


    for(int i=1;i<=graph_data.pnum;i++)
    {
        int x=graph_data.p[i].xx-20;
        int y=graph_data.p[i].yy-20;
        painter.drawEllipse(x,y,40,40);
        QString qs = QString::number(i,10);
        painter.drawText(x+16,y+23,qs);
    }
    if(graph_data.etype==1)
    {
        for(int i=1;i<=graph_data.pnum;i++)
        {
            for(int j=0;j<graph_data.E[i].size();j++)
            {
                int v=graph_data.E[i][j].v;
                double x1=graph_data.p[i].xx;
                double y1=graph_data.p[i].yy;
                double x2=graph_data.p[v].xx;
                double y2=graph_data.p[v].yy;

                QPoint q1;
                q1.setX(x2);
                q1.setY(y2);
                double _length=graph_data.p[i].getlength(q1);
                double tempx=(x2-x1)/_length*10;
                double tempy=(y2-y1)/_length*10;

                x1+=tempx;
                y1+=tempy;
                x2-=tempx;
                y2-=tempy;

                painter.drawLine(x1,y1,x2,y2);
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
                weightx+=tempx;
                weighty+=tempy;
                QString qs = QString::number(graph_data.E[i][j].w,10);
                painter.drawText(weightx+10,weighty+10,qs);
            }
        }
    }
    else
    {
        for(int i=1;i<=graph_data.une_num;i++)
        {
            int u=graph_data.UndirE[i].u;
            int v=graph_data.UndirE[i].v;
            int w=graph_data.UndirE[i].w;

            double x1=graph_data.p[u].xx;
            double y1=graph_data.p[u].yy;
            double x2=graph_data.p[v].xx;
            double y2=graph_data.p[v].yy;

            QPoint q1;
            q1.setX(x2);
            q1.setY(y2);
            double _length=graph_data.p[u].getlength(q1);
            double tempx=(x2-x1)/_length*10;
            double tempy=(y2-y1)/_length*10;

            x1+=tempx;
            y1+=tempy;
            x2-=tempx;
            y2-=tempy;

            painter.drawLine(x1,y1,x2,y2);
            int weightx=(x1+x2)/2;
            int weighty=(y1+y2)/2;
            weightx+=tempx;
            weighty+=tempy;
            QString qs = QString::number(w,10);
            painter.drawText(weightx+10,weighty+10,qs);
        }
    }
}
