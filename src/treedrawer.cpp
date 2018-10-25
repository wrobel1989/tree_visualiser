
#include "treedrawer.h"

#include <QPainter>
#include <QPaintEvent>
#include <QWidget>


TreeDrawer::TreeDrawer()
{
    background = QBrush(QColor(0xff, 0xff, 0xff));

    this->nSampleTrees = 3;
    this->selectedTreeIndex = 0;

    this->treeNames = new char*[this->nSampleTrees];
    this->treeNames[0] = "TreeBig1";
    this->treeNames[1] = "Tree2";
    this->treeNames[2] = "TreeBigBinary3";

    this->sampleTrees = new nodeElement*[this->nSampleTrees];
    for(int i = 0; i < this->nSampleTrees; i++){
        this->sampleTrees[i] = new nodeElement;
    }
    this->assignSampleTrees();

}

TreeDrawer::~TreeDrawer(){
    delete []this->treeNames;
    for(int i = 0; i < this->nSampleTrees; i++){
        delete this->sampleTrees[i];
    }
    delete []this->sampleTrees;
}

void drawTextInBoundingBoxIfFits(QPainter* p, const char* text,
                                 int centerx, int centery, int boundx, int boundy, int fontsize){

    QFont textFont;
    textFont.setPixelSize(fontsize);
    p->setFont(textFont);
    p->drawText(QRect(centerx, centery, boundx, boundy), Qt::AlignCenter, text);
    //TODO : add safety to not to draw text when it does not fit into the bounding box
    // or fall back to some other option - like try dimnishing text until fits (if ever), etc..
}

void TreeDrawer::assignSampleTrees(){
    nodeElement tmp;
    tmp.addNode();
    tmp.addNode();
    tmp.addNode();
    nodeElement* mainbranch0 = tmp.children[0];
    nodeElement* mainbranch1 = tmp.children[1];
    nodeElement* mainbranch2 = tmp.children[2];
    mainbranch0->addString("DeadBeef");
    mainbranch0->addString("abba");
    mainbranch1->addFloat(8.80000005);
    mainbranch1->addFloat(-4.100000);
    mainbranch1->addFloat(6.7e-98);
    mainbranch2->addInt(6);
    mainbranch2->addInt(3);
    mainbranch2->addNode();
    mainbranch2->children[2]->addInt(2);
    mainbranch2->children[2]->addInt(1);
    *(this->sampleTrees[0]) = tmp;
    //second now
    this->sampleTrees[1]->addNode();
    this->sampleTrees[1]->addString("Some leaf text node here..");
    this->sampleTrees[1]->children[1]->addInt(666);
    this->sampleTrees[1]->children[1]->addNode();
    this->sampleTrees[1]->children[1]->children[1]->addNode();
    this->sampleTrees[1]->children[1]->children[1]->children[0]->addFloat(3.14);
    //third sample tree
    // TODO : some regularity here, build binary tree autogenerator for "binary" trees
    this->sampleTrees[2]->addNode();
    this->sampleTrees[2]->addNode();
    this->sampleTrees[2]->children[0]->addNode();
    this->sampleTrees[2]->children[0]->addNode();
    this->sampleTrees[2]->children[1]->addNode();
    this->sampleTrees[2]->children[1]->addNode();
    this->sampleTrees[2]->children[0]->children[0]->addNode();
    this->sampleTrees[2]->children[0]->children[0]->addNode();
    this->sampleTrees[2]->children[0]->children[1]->addNode();
    this->sampleTrees[2]->children[0]->children[1]->addNode();
    this->sampleTrees[2]->children[1]->children[0]->addNode();
    this->sampleTrees[2]->children[1]->children[0]->addNode();
    this->sampleTrees[2]->children[1]->children[1]->addNode();
    this->sampleTrees[2]->children[1]->children[1]->addNode();

    this->sampleTrees[2]->children[0]->children[0]->children[0]->addString("000");
    this->sampleTrees[2]->children[0]->children[0]->children[1]->addString("001");
    this->sampleTrees[2]->children[0]->children[1]->children[0]->addString("010");
    this->sampleTrees[2]->children[0]->children[1]->children[1]->addString("011");
    this->sampleTrees[2]->children[1]->children[0]->children[0]->addString("100");
    this->sampleTrees[2]->children[1]->children[0]->children[1]->addString("101");
    this->sampleTrees[2]->children[1]->children[1]->children[0]->addString("110");
    this->sampleTrees[2]->children[1]->children[1]->children[1]->addString("111");
}

// helper function that paints the tree recursively - element by element
// In the given full window of (widht, height) - the element is matched on the proper Y coord by Ylevel/depth ratio
// For the X access, the parent gets the normalized range at the center of which it draws itself
// and passes subdivided ranges to its children with one level down
void paintElement(int width, int height, QPainter* p, nodeElement* el,
                  int Ylevel, int depth, double xrange_start, double xrange_stop, int margin){

    // center position of this node
    int centerX = (int)(((xrange_start + xrange_stop) / 2.0) * width);
    int centerY = (int)((((double)Ylevel - 1.0) / depth + 0.5 / depth) * height);

    // boundary box for this node element
    int boundboxX = (int)((xrange_stop - xrange_start) * width) - margin;
    int boundboxY = (int)((1.0 / depth) * height) - margin;

    // call children positioning, if present
    if(el->children.size() > 0){
        for(int i = 0; i < el->children.size(); i++){
            double new_range = (xrange_stop - xrange_start) / el->children.size();
            double new_start = i * new_range + xrange_start;
            double new_stop = new_start + new_range;

            int line_end_x = (int)(width * (new_start + new_stop) / 2.0);
            int line_end_y = (int)((((double)Ylevel) / depth + 0.5 / depth) * height);

            p->drawLine(centerX, centerY, line_end_x, line_end_y);

            paintElement(width, height, p, el->children[i], Ylevel + 1,
                         depth, new_start, new_stop, margin);
        }
    }

    switch (el->type){ // do the allocation of the space for value and copy it
        case integer:{
            QBrush brush(QColor(0xff, 0xcc, 0xcc));
            p->setBrush(brush);
            p->drawRect(centerX - boundboxX/2, centerY - boundboxY/2, boundboxX, boundboxY);
            char* buf = new char[1024];
            snprintf(buf, 1024, "%d", *((int*)el->value));
            drawTextInBoundingBoxIfFits(p, buf, centerX-boundboxX/2, centerY-boundboxY/2,
                                        boundboxX, boundboxY, 16);
            delete []buf;
        }
        break;
        case floatpoint:{
            QBrush brush(QColor(0xcc, 0xff, 0xcc));
            p->setBrush(brush);
            p->drawRect(centerX - boundboxX/2, centerY - boundboxY/2, boundboxX, boundboxY);
            char* buf = new char[1024];
            snprintf(buf, 1024, "%g", *((double*)el->value));
            drawTextInBoundingBoxIfFits(p, buf, centerX-boundboxX/2, centerY-boundboxY/2,
                                        boundboxX, boundboxY, 16);
            delete []buf;
        }
        break;
        case string:{
            QBrush brush(QColor(0xcc, 0xcc, 0xff));
            p->setBrush(brush);
            p->drawRect(centerX - boundboxX/2, centerY - boundboxY/2, boundboxX, boundboxY);
            const char* text = (const char*)el->value;
            std::string addquote(text);
            addquote = "\"" + addquote + "\"";
            drawTextInBoundingBoxIfFits(p, addquote.c_str(), centerX-boundboxX/2, centerY-boundboxY/2,
                                        boundboxX, boundboxY, 16);

        }
        break;
        case node:{
            // no text for node
            QBrush brush(QColor(0xbb, 0xbb, 0xbb));
            p->setBrush(brush);
            p->drawEllipse(centerX - boundboxX/2, centerY - boundboxY/2, boundboxX, boundboxY);
        }
        break;
    }

}

void TreeDrawer::paintTree(QPainter* p, nodeElement* tree, int width, int height){
    int depth = tree->getDepth();
    p->setPen(QPen(Qt::black, 4, Qt::SolidLine, Qt::RoundCap));
    paintElement(width, height, p, tree, 1, depth, 0.0, 1.0, 20);
    char* printbuf = new char[256*1024]; //work on 256KB buffer
    tree->serializeToJson(printbuf);
    printf("Painted tree : %s\n", printbuf);
    delete printbuf;
}

void TreeDrawer::paint(QPainter *painter, QPaintEvent *event, int width, int height)
{
    painter->fillRect(event->rect(), background);

    nodeElement tree = *(this->sampleTrees[this->selectedTreeIndex]);
    paintTree(painter, &tree, width, height);

}

