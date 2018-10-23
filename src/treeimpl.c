#include <globaldefs.h>

// actual storage here
const char *objectNames[] = {"Node",
                             "integer",
                             "float",
                             "string"};


nodeElement::nodeElement(){
    this->type = node;
    this->objectName = (char*)objectNames[this->type];
    this->value = NULL;
    this->numberOfChilden = 0;
    this->children = NULL;
}

Tree::Tree(){
    this->parent = new nodeElement;
}


Tree::~Tree(){
    delete this->parent;
}


nodeElement* Tree::getParentNode(){
    return this->parent;
}
