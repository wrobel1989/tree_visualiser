#include "glwidget.h"
#include "window.h"

#include <QGridLayout>
#include <QLabel>
#include <QTimer>

Window::Window()
{
    setWindowTitle(tr("2D Painting on Native and OpenGL Widgets"));
    GLWidget *openGL = new GLWidget(&drawer, this);
    QLabel *openGLLabel = new QLabel(tr("Visualization"));
    openGLLabel->setAlignment(Qt::AlignHCenter);
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(openGL, 0, 1);
    layout->addWidget(openGLLabel, 1, 1);
    setLayout(layout);
}
