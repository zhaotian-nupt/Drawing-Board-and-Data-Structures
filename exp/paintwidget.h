#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QtWidgets>
#include <QDebug>
#include "shape.h"
#include "edge.h"
#include "point.h"
#include "undiredge.h"


class PaintWidget : public QWidget
{
        Q_OBJECT

public:
        PaintWidget(QWidget *parent = 0);

public slots:
        void setCurrentShape(Shape::Code s)
        {
            if(s==Shape::Finish)
            {
                ifpaint=false;
            }
            if(s != currShapeCode) {
                    currShapeCode = s;
            }
        }
        void clear()
        {
            foreach(Shape * shape, shapeList) {
                    shape=NULL;
            }
            shape=NULL;
            ifpaint=true;
            perm=false;
            update();
        }

protected:
        void paintEvent(QPaintEvent *event);
        void mousePressEvent(QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent *event);
        void mouseReleaseEvent(QMouseEvent *event);

private:
        Shape::Code currShapeCode;
        Shape *shape;
        bool perm;
        bool ifpaint;
        QList<Shape*> shapeList;
};

#endif // PAINTWIDGET_H
