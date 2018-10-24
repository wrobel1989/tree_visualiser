#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>

class TreeDrawer;

class GLWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    GLWidget(TreeDrawer *drawer, QWidget *parent);

public slots:
    void animate();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    TreeDrawer *drawer;
};

#endif
