
#ifndef HELPER_H
#define HELPER_H

#include <QBrush>
#include <QFont>
#include <QPen>
#include <QWidget>
#include <globaldefs.h>

class TreeDrawer
{
public:
    TreeDrawer();

public:
    void paint(QPainter *painter, QPaintEvent *event, int width, int height);

private:
    QBrush background;
    QPen textPen;

    nodeElement getSampleTree();
    void paintTree(QPainter* p, nodeElement* tree, int width, int height);

};

#endif
