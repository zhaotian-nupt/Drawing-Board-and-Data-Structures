#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>

#include "shape.h"
#include "paintwidget.h"
#include "paintbeautify.h"
#include "paintbianli.h"
#include "paintmst.h"
#include "paintsp.h"


class MainWindow : public QMainWindow
{
        Q_OBJECT

public:
        MainWindow(QWidget *parent = 0);
        QLabel * label;
        QAction *drawPointAction;

signals:
        void changeCurrentShape(Shape::Code newShape);

private slots:
        void drawEdgeActionTriggered();
        void drawUndirEdgeActionTriggered();
        void drawPointActionTriggered();
        void finishActionTriggered();
        void bianliActionTriggered();
        void drawMSTActionTriggered();
        void drawSPActionTriggered();
        void clearActionTriggered();
};

#endif // MAINWINDOW_H
