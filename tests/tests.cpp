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

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
