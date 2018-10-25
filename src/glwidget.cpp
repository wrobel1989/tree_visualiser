
#include "glwidget.h"
#include "treedrawer.h"

#include <QPainter>
#include <QTimer>

GLWidget::GLWidget(TreeDrawer *helper, QWidget *parent)
    : QOpenGLWidget(parent), drawer(helper)
{
    setFixedSize(1200, 700);
    setAutoFillBackground(false);
}

void GLWidget::animate()
{
    update();
}

void GLWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    drawer->paint(&painter, event, this->width(), this->height());
    painter.end();
}
