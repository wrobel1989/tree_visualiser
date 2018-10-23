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
    int cmp_string_content_result1 = strcmp(empty.getParentNode()->objectName, "integer"); //returned 0 means strings equal
    ASSERT_NE(0, cmp_string_content_result1); //assert it is not "integer"
    int cmp_string_content_result2 = strcmp(empty.getParentNode()->objectName, "Node");
    ASSERT_EQ(0, cmp_string_content_result2); //assert it is "Node" - that is the correct name for the
    //empty element the Node has right now
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
