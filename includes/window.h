#ifndef WINDOW_H
#define WINDOW_H

#include "treedrawer.h"

#include <QWidget>

class Window : public QWidget
{
    Q_OBJECT

public:
    Window();

private:
    TreeDrawer drawer;
};

#endif
