#include "glwidget.h"
#include "window.h"

#include <QGridLayout>
#include <QLabel>
#include <QComboBox>
#include <stdio.h>
#include <globaldefs.h>

void Window::optionSelected(int option){
    this->openGL->setTreeIndex(option);
    this->openGL->update();
    char* printbuf = new char[256*1024]; //work on 256KB buffer
    this->drawer.getSampleTrees()[option]->serializeToJson(printbuf);
    this->openGLLabel->setText(tr(printbuf));
    this->openGLLabel->update();
    delete []printbuf;
}

Window::Window()
{
    setWindowTitle(tr("2D Painting on Native and OpenGL Widgets"));
    this->openGL = new GLWidget(&drawer, this);
    openGLLabel = new QLabel(tr("Visualization"));
    openGLLabel->setAlignment(Qt::AlignHCenter);
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(openGL, 0, 1);
    layout->addWidget(openGLLabel, 1, 1);
    this->optionSelected(0);
    QComboBox *comboBox = new QComboBox;
    for(int i = 0; i < this->drawer.getTreeNums(); i++){
        comboBox->addItem(tr(this->drawer.getTreeNames()[i]));
    }
    layout->addWidget(comboBox, 2, 1);
    connect(comboBox,SIGNAL(activated(int)),this,SLOT(optionSelected(int)));
    setLayout(layout);
}
