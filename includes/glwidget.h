#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <treedrawer.h>


class GLWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    GLWidget(TreeDrawer *drawer, QWidget *parent);

    char** getTreeNames() {return drawer->getTreeNames();}
    void setTreeIndex(int index) {drawer->setTreeIndex(index);}

public slots:
    void animate();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    TreeDrawer *drawer;
};

#endif
