#include "paintbeautify.h"
#include "data.h"

extern Data graph_data;

PaintBeautify::PaintBeautify(QWidget *parent)
{

}
void PaintBeautify::paintEvent(QPaintEvent *event)
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

    if(graph_data.type==3)
    {
        int x0=480;
        int y0=350;
        int num=graph_data.pnum;
        double PI = acos(-1.0);
        double du=2.0*PI/num;
        int r=200;
        for(int i=1;i<=num;i++)
        {
            int x=x0+r*cos(PI/2-(i-1)*du);
            int y=y0+r*sin(PI/2-(i-1)*du);
            painter.drawEllipse(x,y,40,40);
            QString qs = QString::number(i,10);
            painter.drawText(x+16,y+23,qs);
            graph_data.p[i].xx=x+20;
            graph_data.p[i].yy=y+20;
        }
    }

    if(graph_data.etype==1)
    {
        if(graph_data.type==1)
        {
            int x0=450;
            int cnt=0;
            int y0=50;
            int x,y;
            int level=graph_data.level;
            int height=500/level;
            QStack <int> s;
            bool vis[100];
            memset(vis,false,sizeof(vis));
            int t=graph_data.root[1];
            s.push(t);

            pen.setColor(QColor(255, 0, 0));
            painter.setPen(pen);
            painter.drawEllipse(x0,y0,40,40);
            QString qs = QString::number(t,10);
            painter.drawText(x0+16,y0+23,qs);
            graph_data.p[t].xx=x0+20;
            graph_data.p[t].yy=y0+20;
            pen.setColor(QColor(0, 0, 0));
            painter.setPen(pen);

            while(!s.empty())
            {
                int now = s.top();
                vis[now]=true;
                int i;
                for(i=0;i<graph_data.E[now].size();i++)
                {
                    if(!vis[graph_data.E[now][i].v])
                    {
                        t=graph_data.E[now][i].v;
                        s.push(t);
                        int tsize=graph_data.E[now].size();
                        x0=graph_data.p[now].xx-20;
                        if(tsize%2==1)
                        {
                            if(i<graph_data.E[now].size()/2)
                                x=x0-(graph_data.E[now].size()/2-i)*(1500/(graph_data.p[t].level*graph_data.p[t].level*graph_data.p[t].level));
                            else if(i==graph_data.E[now].size()/2)
                                x=x0;
                            else
                                x=x0+(i-graph_data.E[now].size()/2)*(1500/(graph_data.p[t].level*graph_data.p[t].level*graph_data.p[t].level));
                        }
                        else
                        {
                            if(i<graph_data.E[now].size()/2)
                                x=x0-(graph_data.E[now].size()/2-i)*(1500/(graph_data.p[t].level*graph_data.p[t].level*graph_data.p[t].level));
                            else
                                x=x0+(i+1-graph_data.E[now].size()/2)*(1500/(graph_data.p[t].level*graph_data.p[t].level*graph_data.p[t].level));
                        }
                        y=y0+(graph_data.p[t].level-1)*height;
                        painter.drawEllipse(x,y,40,40);
                        QString qs = QString::number(t,10);
                        painter.drawText(x+16,y+23,qs);
                        graph_data.p[t].xx=x+20;
                        graph_data.p[t].yy=y+20;
                        break;
                    }
                }
                if(i==graph_data.E[now].size())
                {
                    s.pop();
                }
            }
        }

        if(graph_data.type==2)
        {
            for(int k=1;k<=graph_data.rootnum;k++)
            {
                int x0=200+320*(k-1);
                int cnt=0;
                int y0=100;
                int x,y;
                int level=graph_data.level;
                int height=500/level;
                QStack <int> s;
                bool vis[100];
                memset(vis,false,sizeof(vis));
                int t=graph_data.root[k];
                s.push(t);
                pen.setColor(QColor(255, 0, 0));
                painter.setPen(pen);
                painter.drawEllipse(x0,y0,40,40);
                QString qs = QString::number(t,10);
                painter.drawText(x0+16,y0+23,qs);
                graph_data.p[t].xx=x0+20;
                graph_data.p[t].yy=y0+20;
                pen.setColor(QColor(0, 0, 0));
                painter.setPen(pen);

                while(!s.empty())
                {
                    int now = s.top();
                    vis[now]=true;
                    int i;
                    for(i=0;i<graph_data.E[now].size();i++)
                    {
                        if(!vis[graph_data.E[now][i].v])
                        {
                            t=graph_data.E[now][i].v;
                            s.push(t);
                            int tsize=graph_data.E[now].size();
                            x0=graph_data.p[now].xx-20;
                            if(tsize%2==1)
                            {
                                if(i<graph_data.E[now].size()/2)
                                    x=x0-(graph_data.E[now].size()/2-i)*(160/graph_data.p[t].level);
                                else if(i==graph_data.E[now].size()/2)
                                    x=x0;
                                else
                                    x=x0+(i-graph_data.E[now].size()/2)*(160/graph_data.p[t].level);
                            }
                            else
                            {
                                if(i<graph_data.E[now].size()/2)
                                    x=x0-(graph_data.E[now].size()/2-i)*(160/graph_data.p[t].level);
                                else
                                    x=x0+(i+1-graph_data.E[now].size()/2)*(160/graph_data.p[t].level);
                            }
                            y=y0+(graph_data.p[t].level-1)*height;
                            painter.drawEllipse(x,y,40,40);
                            QString qs = QString::number(t,10);
                            painter.drawText(x+16,y+23,qs);
                            graph_data.p[t].xx=x+20;
                            graph_data.p[t].yy=y+20;
                            break;
                        }
                    }
                    if(i==graph_data.E[now].size())
                    {
                        s.pop();
                    }
                }
            }
        }

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
    else if(graph_data.etype==2)
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
