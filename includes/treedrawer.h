
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
    ~TreeDrawer();

public:
    void paint(QPainter *painter, QPaintEvent *event, int width, int height);

    char** getTreeNames(){return treeNames;}
    int getTreeNums() {return nSampleTrees;}
    void setTreeIndex(int idx) {this->selectedTreeIndex = idx;}
    nodeElement** getSampleTrees() {return this->sampleTrees;}

private:
    QBrush background;
    QPen textPen;

    void assignSampleTrees();
    void paintTree(QPainter* p, nodeElement* tree, int width, int height);

    int nSampleTrees;
    int selectedTreeIndex;
    char** treeNames;
    nodeElement** sampleTrees;
};

#endif
