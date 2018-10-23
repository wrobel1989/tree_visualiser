#include <globaldefs.h>
#include <string.h>
#include <stdio.h>

// actual storage here
const char *objectNames[] = {"Node",
                             "integer",
                             "float",
                             "string"};

//comparators - how we can compare the 2 primitive types of the same type
// for a > b - returns 1
// for a < b - returns -1
// for a == b - returns 0
// for integers and floats we can compare them as well, since casting of int to double is perfectly valid operation
// comparing strings/int or strings/floats is undefined
template<typename T1, typename T2>
int compare(const T1& a, const T2& b){
    if(a == b)
        return 0;
    if(a > b)
        return 1;
    if(a < b)
        return -1;
}

//also, the special case for comparing strings - we do not want to compare pointers values on the string memory
//but the string content itself
int compare(const char* a, const char* b){
    return strcmp(a, b); // restore to strcmp for now
}

int compare(const nodeElement& a, const nodeElement& b){
    if(a.type == b.type && a.type == integer){ //we only know how to compare leaf elements of the same type
        return compare(*((int*)a.value), *((int*)b.value));
    }
    if(a.type == b.type && a.type == floatpoint){ //we only know how to compare leaf elements of the same type
        return compare(*((double*)a.value), *((double*)b.value));
    }
    if(a.type == b.type && a.type == string){ //we only know how to compare leaf elements of the same type
        return compare(((const char*)a.value), ((const char*)b.value));
    }
    // TODO : allow comparing integer to float - since their conversion makes sense
    return 1;
}

nodeElement::nodeElement(){
    this->type = node;
    this->objectName = (char*)objectNames[this->type];
    this->value = NULL;
    this->children.resize(0);
}

//helper function that is called recursively - walks the tree, copy at each entry untill leafs found
void copy_tree_recursively(const nodeElement& root_src, nodeElement* dst){
    //copy main root element values
    dst->type = root_src.type;
    dst->objectName = root_src.objectName;
    switch (dst->type){ // do the allocation of the space for value and copy it
        case integer:{
            dst->value = (void*) new int;
            *((int*)dst->value) = *((int*)root_src.value);
        }
        break;
        case floatpoint:{
            dst->value = (void*) new double;
            *((double*)dst->value) = *((double*)root_src.value);
        }
        break;
        case string:{
            dst->value = (void*)new char[strlen(((char*)root_src.value))+1];
            strcpy((char*)dst->value, (const char*)root_src.value);
        }
        break;
        case node:{
            dst->value = NULL;
        }
        break;
    }
    if(root_src.children.size() > 0){
        dst->children.resize(root_src.children.size());
        for(int i = 0; i < root_src.children.size(); i++){
            dst->children[i] = new nodeElement;
            copy_tree_recursively(*(root_src.children[i]), dst->children[i]);
        }
    }
}

nodeElement& nodeElement::operator=(const nodeElement& old){
    copy_tree_recursively(old, this);
    return *this;
}

nodeElement::nodeElement(const nodeElement& old_root){
    //recursion starts here
    copy_tree_recursively(old_root, this);
}

nodeElement::~nodeElement(){
    if(this->children.size() > 0){
        // if size > 0, then the pointers for the children must be valid
        for(int i = 0; i < this->children.size(); i++){
            nodeElement* child = this->children[i];
            delete child;//will further call destructors of the children that will walk down the tree
        }
    }else{
        //Means, we have primitive type, depending on the type, delete its heap-stored data
        switch (this->type){
            case integer:{
                int* ival = (int*)this->value;
                delete ival;
            }
            break;
            case floatpoint:{
                double* fval = (double*)this->value;
                delete fval;
            }
            break;
            case string:{
                char* cval = (char*)this->value;
                delete []cval;
            }
            break;
        }
    }

}

int searchbinary(nodeElement* parent, int start_idx, int stop_idx, nodeElement* to_search){
    if(start_idx == stop_idx)
        return start_idx;
    // stop is not before start..
    if (start_idx > stop_idx)
        return -1;

    int middle = start_idx + (stop_idx - start_idx)/2;
    if(compare(*(parent->children[middle]), *to_search) == 0){
        return middle;
    }
    //if element to insert is smaller than middle - it is located in the subarray on the left
    if(compare(*(parent->children[middle]), *to_search) == 1){
        return searchbinary(parent, start_idx, middle, to_search);
    }else{
        return searchbinary(parent, middle + 1, stop_idx, to_search);
    }

}

int nodeElement::binarySearchForIndexToInsertIntoSortedLeafs(nodeElement* to_search){
    searchbinary(this, 0, this->children.size(), to_search);
}

void nodeElement::addInt(int integer_value_of_child){
    nodeElement *intleaf = new nodeElement;
    intleaf->value = (void*)new int;
    *((int*)intleaf->value) = integer_value_of_child;
    intleaf->type = integer;
    intleaf->objectName = objectNames[intleaf->type]; //type name is shared string - so this not needs to be object-owned memory
    intleaf->children.resize(0); //no children for the int leaf

    if (this->children.size() == 0){
        //insert if empty
        this->children.push_back(intleaf);
    } else {
        // if not empty - find correct place in sorted array - so the leafs will be always sorted
        int insertion_idx = this->binarySearchForIndexToInsertIntoSortedLeafs(intleaf);
        if(insertion_idx == -1) printf("Warn - -1 found!\n");
        this->children.insert(this->children.begin()+insertion_idx, intleaf);
    }

}

void nodeElement::addFloat(double floatpoint_value_of_child){
    nodeElement *floatpointleaf = new nodeElement;
    floatpointleaf->value = (void*)new double;
    *((double*)floatpointleaf->value) = floatpoint_value_of_child;
    floatpointleaf->type = floatpoint;
    floatpointleaf->objectName = objectNames[floatpointleaf->type];
    floatpointleaf->children.resize(0);
    if (this->children.size() == 0){
        this->children.push_back(floatpointleaf);
    } else {
        int insertion_idx = this->binarySearchForIndexToInsertIntoSortedLeafs(floatpointleaf);
        this->children.insert(this->children.begin()+insertion_idx, floatpointleaf);
    }
}

void nodeElement::addString(const char* string_value_to_add){
    nodeElement *stringleaf = new nodeElement;
    stringleaf->value = (void*)new char[strlen(string_value_to_add)+1];
    strcpy((char*)stringleaf->value, string_value_to_add);
    stringleaf->type = floatpoint;
    stringleaf->objectName = objectNames[stringleaf->type];
    stringleaf->children.resize(0);
    if (this->children.size() == 0){
        this->children.push_back(stringleaf);
    } else {
        int insertion_idx = this->binarySearchForIndexToInsertIntoSortedLeafs(stringleaf);
        this->children.insert(this->children.begin()+insertion_idx, stringleaf);
    }
}

void nodeElement::addNode(const nodeElement& element){
    nodeElement *nodeleaf = new nodeElement;
    copy_tree_recursively(element, nodeleaf);
    this->children.push_back(nodeleaf);
}

void nodeElement::addNode(){
    nodeElement *nodeleaf = new nodeElement;
    this->children.push_back(nodeleaf);
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
