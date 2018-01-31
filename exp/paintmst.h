#ifndef PAINTMST_H
#define PAINTMST_H

#include <QWidget>
#include <qpainter.h>
#include "data.h"

class PaintMST : public QWidget
{
public:
    PaintMST(QWidget *parent = 0);

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // PAINTMST_H
