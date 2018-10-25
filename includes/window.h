#ifndef WINDOW_H
#define WINDOW_H

#include "treedrawer.h"

#include <QWidget>
#include <QMessageBox>

class GLWidget;

class Window : public QWidget
{
    Q_OBJECT

public:
    Window();

public slots:
    void optionSelected(int);

private:
    TreeDrawer drawer;
    GLWidget *openGL;
    QLabel *openGLLabel;
};

#endif
