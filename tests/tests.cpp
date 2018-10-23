//here goes the main tests code.
#include <globaldefs.h>

// on ubuntu, make sure to do the "sudo apt-get install libgtest-dev" to have
// gtest with headers installed
#include <gtest/gtest.h>

#define GTEST_COUT std::cerr << "[          ] [ INFO ]"

//create empty tree with empty parent node and sanitize it
TEST(SanityEmptyTreeTest, EmptyTreeIsNullAndHasCorrectName) {
    Tree empty;
    GTEST_COUT << "Right now, I am creating the empty tree with one empty node" << std::endl;
    GTEST_COUT << "And checking if that node has the correct type, typename and if it is "
                  "indeed empty of any children" << std::endl;
    ASSERT_EQ(0, empty.getParentNode()->children.size());
    ASSERT_EQ(node, empty.getParentNode()->type);
    ASSERT_EQ(NULL, empty.getParentNode()->value);
    int cmp_string_content_result1 = strcmp(empty.getParentNode()->objectName, "integer"); //returned 0 means strings equal
    ASSERT_NE(0, cmp_string_content_result1); //assert it is not "integer"
    int cmp_string_content_result2 = strcmp(empty.getParentNode()->objectName, "Node");
    ASSERT_EQ(0, cmp_string_content_result2); //assert it is "Node" - that is the correct name for the
    //empty element the Node has right now
}

TEST(SimpleIntTest, IntInsertionSanity) {
    Tree intTree;
    intTree.getParentNode()->addInt(2);
    intTree.getParentNode()->addInt(3);
    intTree.getParentNode()->addInt(7);
    GTEST_COUT << "Right now, I am creating tree with only 3 integer leafs within it" << std::endl;
    GTEST_COUT << "I'm checking if indeed 3 elements are present" << std::endl;
    ASSERT_EQ(3, intTree.getParentNode()->children.size());
}

TEST(SimpleIntTest, IntIsSorted) {
    Tree intTree;
    intTree.getParentNode()->addInt(8);
    intTree.getParentNode()->addInt(3);
    intTree.getParentNode()->addInt(7);
    intTree.getParentNode()->addInt(5);
    intTree.getParentNode()->addInt(1);
    intTree.getParentNode()->addInt(8);
    GTEST_COUT << "Right now, I am creating tree with only 6 integer leafs within it : 8 3 7 5 1 9" << std::endl;
    GTEST_COUT << "I'm checking if indeed those 6 elements are present and sorted - when added" << std::endl;
    ASSERT_EQ(6, intTree.getParentNode()->children.size());

    ASSERT_EQ(1, *((int*)intTree.getParentNode()->children[0]->value));
    ASSERT_EQ(3, *((int*)intTree.getParentNode()->children[1]->value));
    ASSERT_EQ(5, *((int*)intTree.getParentNode()->children[2]->value));
    ASSERT_EQ(7, *((int*)intTree.getParentNode()->children[3]->value));
    ASSERT_EQ(8, *((int*)intTree.getParentNode()->children[4]->value));
    ASSERT_EQ(8, *((int*)intTree.getParentNode()->children[5]->value));
}

TEST(SimpleFloatPointTest, FloatPointIsSorted) {
    Tree floatTree;
    floatTree.getParentNode()->addFloat(10.1);
    floatTree.getParentNode()->addFloat(-5.2);
    floatTree.getParentNode()->addFloat(7.0);
    floatTree.getParentNode()->addFloat(50.9);
    floatTree.getParentNode()->addFloat(66.6);
    floatTree.getParentNode()->addFloat(-22.1);
    GTEST_COUT << "Right now, I am creating tree with only 6 floatpoint leafs within it : 10.1 -5.2 7.0 50.9 66.6 -22.1" << std::endl;
    GTEST_COUT << "I'm checking if indeed those 6 elements are present and sorted - when added" << std::endl;
    ASSERT_EQ(6, floatTree.getParentNode()->children.size());

    ASSERT_EQ(-22.1, *((double*)floatTree.getParentNode()->children[0]->value));
    ASSERT_EQ(-5.2,  *((double*)floatTree.getParentNode()->children[1]->value));
    ASSERT_EQ(7.0,   *((double*)floatTree.getParentNode()->children[2]->value));
    ASSERT_EQ(10.1,  *((double*)floatTree.getParentNode()->children[3]->value));
    ASSERT_EQ(50.9,  *((double*)floatTree.getParentNode()->children[4]->value));
    ASSERT_EQ(66.6,  *((double*)floatTree.getParentNode()->children[5]->value));
}

TEST(SimpleStringTest, StringInsertionSanity) {
    Tree strTree;
    strTree.getParentNode()->addString("abd");
    strTree.getParentNode()->addString("abc");
    strTree.getParentNode()->addString("xylitol");
    strTree.getParentNode()->addString("deadbeef");
    GTEST_COUT << "Right now, I am creating tree with only 4 strings leafs within it" << std::endl;
    GTEST_COUT << "I'm checking if indeed 4 elements are present and if the strings are sorted" << std::endl;
    ASSERT_EQ(4, strTree.getParentNode()->children.size());

    int cmp_string_content_result1 = strcmp((const char*)strTree.getParentNode()->children[0]->value, "abc"); //returned 0 means strings equal
    int cmp_string_content_result2 = strcmp((const char*)strTree.getParentNode()->children[1]->value, "abd"); //returned 0 means strings equal
    int cmp_string_content_result3 = strcmp((const char*)strTree.getParentNode()->children[2]->value, "deadbeef"); //returned 0 means strings equal
    int cmp_string_content_result4 = strcmp((const char*)strTree.getParentNode()->children[3]->value, "xylitol"); //returned 0 means strings equal
    ASSERT_EQ(0, cmp_string_content_result1);
    ASSERT_EQ(0, cmp_string_content_result2);
    ASSERT_EQ(0, cmp_string_content_result3);
    ASSERT_EQ(0, cmp_string_content_result4);
}

TEST(SimpleCopyTest, SanitizeTreeCopy) {
    Tree tree;
    nodeElement* rootNode = tree.getParentNode();
    {
        nodeElement tmp;
        tmp.addNode();
        tmp.addNode();
        tmp.addNode();
        nodeElement* mainbranch0 = tmp.children[0];
        nodeElement* mainbranch1 = tmp.children[1];
        nodeElement* mainbranch2 = tmp.children[2];
        mainbranch0->addInt(3);
        mainbranch0->addInt(7);
        mainbranch0->addInt(1);
        mainbranch1->addFloat(8.8);
        mainbranch1->addFloat(-4.1);
        mainbranch2->addString("DeadBeef");
        *rootNode = tmp;
        //tmp gets destroyed - out of scope - check if root got correctly copied
    }
    GTEST_COUT << "Right now, I am creating a tree with three branches - one for the 3 ints, one for 2 floats and one for string" << std::endl;
    GTEST_COUT << "I'm checking if the main tree gets preserved with the correct data in the heap - even after tmp goes out of scope and gets destroyed" << std::endl;
    ASSERT_EQ(3, rootNode->children.size());
    ASSERT_EQ(3, rootNode->children[0]->children.size());
    ASSERT_EQ(2, rootNode->children[1]->children.size());
    ASSERT_EQ(1, rootNode->children[2]->children.size());
    //assert content as well
    ASSERT_EQ(1, *((int*)rootNode->children[0]->children[0]->value));
    ASSERT_EQ(3, *((int*)rootNode->children[0]->children[1]->value));
    ASSERT_EQ(7, *((int*)rootNode->children[0]->children[2]->value));
    ASSERT_EQ(-4.1, *((double*)rootNode->children[1]->children[0]->value));
    ASSERT_EQ(8.8,  *((double*)rootNode->children[1]->children[1]->value));
    int cmp_string_content_result = strcmp((const char*)rootNode->children[2]->children[0]->value, "DeadBeef");
    ASSERT_EQ(0, cmp_string_content_result);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
