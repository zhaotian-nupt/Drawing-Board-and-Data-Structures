#include "paintwidget.h"
#include "data.h"

extern Data graph_data;

PaintWidget::PaintWidget(QWidget *parent)
        : QWidget(parent), currShapeCode(Shape::Point), shape(NULL), perm(false),ifpaint(true)
{
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void PaintWidget::paintEvent(QPaintEvent *event)
{
        QPainter painter(this);
        painter.setBrush(Qt::white);
        painter.drawRect(0, 0, size().width(), size().height());

        QPen pen;
        pen.setWidth(2);
        painter.setPen(pen);

        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        painter.setFont(font);

        foreach(Shape * shape, shapeList) {
                shape->paint(painter);
        }
        if(shape) {
                shape->paint(painter);
        }
}

void PaintWidget::mousePressEvent(QMouseEvent *event)
{
    if(ifpaint)
    {
        switch(currShapeCode)
        {
        case Shape::Edge:
                {
                        if(graph_data.etype==2)
                            shape = NULL;
                        else
                            shape = new Edge;
                        break;
                }
        case Shape::Point:
                {
                        shape = new Point;
                        break;
                }
        case Shape::UndirEdge:
                {
                    if(graph_data.etype==1)
                        shape = NULL;
                    else
                        shape = new UndirEdge;
                    break;
                }
        }
        if(shape != NULL) {
                perm = false;
                shapeList<<shape;
                shape->setStart(event->pos());
                shape->setEnd(event->pos());
                switch(currShapeCode)
                {
                case Shape::Point:
                    {
                        graph_data.pnum++;
                        shape->id=graph_data.pnum;
                        graph_data.p[graph_data.pnum].x1=shape->start.x();
                        graph_data.p[graph_data.pnum].y1=shape->start.y();
                    }
                }
        }
    }
}

void PaintWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(ifpaint)
    {
        if(shape && !perm) {
                shape->setEnd(event->pos());

                switch(currShapeCode)
                {
                case Shape::Point:
                    {
                        graph_data.p[graph_data.pnum].x2=shape->end.x();
                        graph_data.p[graph_data.pnum].y2=shape->end.y();
                        graph_data.p[graph_data.pnum].update_r();
                    }
                }
                update();
        }
    }
}

void PaintWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(perm)
        return;
    if(ifpaint)
    {
        switch(currShapeCode)
        {
        case Shape::Edge:
            {
                int id1=0,id2=0;
                double temp1=99999999.0;
                double temp2=99999999.0;

                for(int i=1;i<=graph_data.pnum;i++)
                {
                    if(i==id1)continue;
                    if(graph_data.p[i].getlength(shape->start)<temp1)
                    {
                        id1=i;
                        temp1=graph_data.p[i].getlength(shape->start);
                    }

                }
                for(int i=1;i<=graph_data.pnum;i++)
                {
                    if(i==id1 || i==id2)continue;
                    if(graph_data.p[i].getlength(shape->end)<temp2)
                    {
                        id2=i;
                        temp2=graph_data.p[i].getlength(shape->end);
                    }
                }

                QPoint _start,_end;
                _start.setX(graph_data.p[id1].xx);
                _start.setY(graph_data.p[id1].yy);
                _end.setX(graph_data.p[id2].xx);
                _end.setY(graph_data.p[id2].yy);
                shape->setStart(_start);
                shape->setEnd(_end);
                update();

                if(id1!=0 && id2!=0 &&id1!=id2)
                {
                    graph_data.etype=1;
                    bool isOK;
                    QString text = QInputDialog::getText(NULL, "Input weight",
                                                                       "Please input wight of the edge",
                                                                       QLineEdit::Normal,
                                                                       "0",
                                                                       &isOK);
                    if(isOK)
                    {
                        bool ifok;
                        int weight=text.toInt(&ifok,10);
                        if(ifok)
                        {
                            graph_data.addedge(id1,id2,weight);
                            shape->W=weight;
                        }
                        printf("%d\n",weight);
                    }
                    else
                    {
                        graph_data.addedge(id1,id2,0);
                        shape->W=1;
                    }
                }
                update();
                break;

            }
        case Shape::Point:
            {
                break;
            }
        case Shape::UndirEdge:
            {
                int id1=0,id2=0;
                double temp1=99999999.0;
                double temp2=99999999.0;

                for(int i=1;i<=graph_data.pnum;i++)
                {
                    if(i==id1)continue;
                    if(graph_data.p[i].getlength(shape->start)<temp1)
                    {
                        id1=i;
                        temp1=graph_data.p[i].getlength(shape->start);
                    }
                }
                for(int i=1;i<=graph_data.pnum;i++)
                {
                    if(i==id1 || i==id2)continue;
                    if(graph_data.p[i].getlength(shape->end)<temp2)
                    {
                        id2=i;
                        temp2=graph_data.p[i].getlength(shape->end);
                    }
                }
                QPoint _start,_end;
                _start.setX(graph_data.p[id1].xx);
                _start.setY(graph_data.p[id1].yy);
                _end.setX(graph_data.p[id2].xx);
                _end.setY(graph_data.p[id2].yy);
                shape->setStart(_start);
                shape->setEnd(_end);
                update();

                if(id1!=0 && id2!=0 &&id1!=id2)
                {
                    graph_data.etype=2;
                    bool isOK;
                    QString text = QInputDialog::getText(NULL, "Input weight",
                                                                       "Please input wight of the edge",
                                                                       QLineEdit::Normal,
                                                                       "0",
                                                                       &isOK);
                    if(isOK)
                    {
                        bool ifok;
                        int weight=text.toInt(&ifok,10);
                        if(ifok)
                        {
                            graph_data.addundiredge(id1,id2,weight);
                            graph_data.addedge(id1,id2,weight);
                            graph_data.addedge(id2,id1,weight);
                            shape->W=weight;
                        }
                    }
                    else
                    {
                        graph_data.addundiredge(id1,id2,1);
                        graph_data.addedge(id1,id2,1);
                        graph_data.addedge(id2,id1,1);
                        shape->W=1;
                    }
                }
                update();
                break;
            }
        }
        perm = true;
    }
}
