
#ifndef HELPER_H
#define HELPER_H

#include <QBrush>
#include <QFont>
#include <QPen>
#include <QWidget>

class TreeDrawer
{
public:
    TreeDrawer();

public:
    void paint(QPainter *painter, QPaintEvent *event, int width, int height);

private:
    QBrush background;
    QFont textFont;
    QPen textPen;
};

#endif
