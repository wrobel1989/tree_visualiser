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
    this->children.resize(0);
}

nodeElement::~nodeElement(){
    if(this->children.size() > 0){
        // if size > 0, then the pointers for the children must be valid
        for(int i = 0; i < this->children.size(); i++){
            nodeElement* child = this->children[i];
            delete child;
        }
    }
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
