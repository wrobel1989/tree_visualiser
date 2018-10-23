#include <cstddef>
#include <vector>

// defines list of types, that we support
enum elementType {
    node = 0, // means this element is node - its name = "node" - it can holds other siblings
              // no other meaningfull data are stored in the node.
    // these are possible options for the leafs - they carry no children then
    integer, //integer
    floatpoint, //double
    string, //string
    // ..
    NumberOfElementTypes //dummy for getting the type count
};

//this directly holds the names for the types we define above. Stored in treeimpl.c - to avoid
//generating multiple symbols storage by linker, when including the same header in different files
extern const char *objectNames[];

// This is a straightforward representation of a single node element in the tree
// Every node structure starts from a "parent", which has no parent
// element - parent element pointer is NULL
// Every leaf of the tree has its children count set to 0
struct nodeElement {
    //these are required
    void* value; // this holds the general purpose data for leaf primitive type.
    // the type is determined by type information - using that type, we can properly interpret data for
    // the primitive type

    char* objectName; //this is directly connected to the type - it holds human-readable name for the type
    // it can point to one of the string in the objectNames

    //these we define ourselves
    // we determine the type. this directly connects to the objectName above
    elementType type;
    std::vector<nodeElement*> children; //array of pointers to the children elements - of size numberOfChilden

    nodeElement(); //construct empty element of type "Node"
    ~nodeElement(); //destructor of the node - calls the destructors of its children - if present
};

typedef nodeElement nodeElement;



// this helper wraps the tree + the API for doing the operations on it
struct Tree {
private:
    nodeElement* parent;
public:
    nodeElement* getParentNode();
    Tree(); //construct empty tree
    ~Tree(); //destroy tree
};
