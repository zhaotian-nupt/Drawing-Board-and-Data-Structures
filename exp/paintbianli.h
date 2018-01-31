#ifndef PAINTBIANLI_H
#define PAINTBIANLI_H

#include <QWidget>
#include <qpainter.h>
#include "data.h"

class PaintBianli : public QWidget
{
public:
    PaintBianli(QWidget *parent = 0);
    void Bianli();

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // PAINTBIANLI_H
