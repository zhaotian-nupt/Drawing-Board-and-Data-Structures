#include "paintmst.h"

extern Data graph_data;

PaintMST::PaintMST(QWidget *parent)
{

}

int Mstfind(int x,int F[])
{
    if(F[x]==-1)return x;
    else return F[x]=Mstfind(F[x],F);
}

void PaintMST::paintEvent(QPaintEvent *event)
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

    int F[100];
    memset(F,-1,sizeof(F));
    int cnt=0;
    int ans=0;
    for(int i=1;i<=graph_data.une_num;i++)
    {
        int u=graph_data.UndirE[i].u;
        int v=graph_data.UndirE[i].v;
        int w=graph_data.UndirE[i].w;
        int t1=Mstfind(u,F);
        int t2=Mstfind(v,F);
        if(t1!=t2)
        {
            ans+=w;
            F[t1]=t2;
            cnt++;

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
        if(cnt==graph_data.pnum-1)break;
    }
}
