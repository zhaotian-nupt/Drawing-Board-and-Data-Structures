#ifndef PAINTSP_H
#define PAINTSP_H

#include <QWidget>
#include <qpainter.h>
#include "data.h"

class PaintSP : public QWidget
{
public:
    PaintSP(QWidget *parent = 0);

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // PAINTSP_H
