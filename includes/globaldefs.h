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

    const char* objectName; //this is directly connected to the type - it holds human-readable name for the type
    // it can point to one of the string in the objectNames

    //these we define ourselves
    // we determine the type. this directly connects to the objectName above
    elementType type;
    std::vector<nodeElement*> children; //array of pointers to the children elements - of size numberOfChilden

    nodeElement(); //construct empty element of type "Node"
    ~nodeElement(); //destructor of the node - calls the destructors of its children - if present

    nodeElement(const nodeElement& old_root); // copy constructor that takes care of copying the heap stuff
    nodeElement& operator=(const nodeElement& old); // assignment operator is also supposed to make full copy of subtree
    bool isLeaf(){return children.size() == 0;} //helper function to tell if this is the leaf node

    // the leaf node holds the memory for the heap-storage of the data for the elements below
    void addInt(int integer_value_of_child); //adds node of integer type as a leaf for this node
    void addFloat(double floatpoint_value_of_child); //the same as integer, but for the float-point value
    void addString(const char* string_value_to_add); //the same as above, but for string.

    void addNode(const nodeElement& element); //adds new child node. Copy is made and managed in the tree
    void addNode(); //add empty node

    //will print to buffer using sprintf. Assumes the passed chunk of memory in "buffer" has enough space.
    void serializeToJson(char* buffer);

private:
    int binarySearchForIndexToInsertIntoSortedLeafs(nodeElement* to_search); // this search the index that the new leaf should be
    //inserted. If at that level, some non-primitive node is present - it ignores it -
    //since it is undefined how to compare float or int with the general-purpose nodeElement
    //Also, that way of insert will keep the node elements (within one type) always sorted
};




// this helper wraps the tree
struct Tree {
private:
    nodeElement* parent;
public:
    nodeElement* getParentNode();
    Tree(); //construct empty tree
    ~Tree(); //destroy tree
};
