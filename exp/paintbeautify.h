#ifndef PAINTBEAUTIFY_H
#define PAINTBEAUTIFY_H

#include <QWidget>
#include <qpainter.h>

class PaintBeautify : public QWidget
{
public:
    PaintBeautify(QWidget *parent = 0);

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // PAINTBEAUTIFY_H
