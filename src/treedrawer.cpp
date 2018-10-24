
#include "treedrawer.h"

#include <QPainter>
#include <QPaintEvent>
#include <QWidget>

TreeDrawer::TreeDrawer()
{
    background = QBrush(QColor(0xff, 0xff, 0xff));
    textFont.setPixelSize(10);
}

void TreeDrawer::paint(QPainter *painter, QPaintEvent *event, int width, int height)
{
    painter->fillRect(event->rect(), background);
    painter->drawEllipse(width/2-50, height/2-50, 100, 100);
    painter->setFont(textFont);
    painter->drawText(QRect(width/2-50, height/2-50, 100, 100), Qt::AlignCenter, QStringLiteral("dummy node.."));
}
