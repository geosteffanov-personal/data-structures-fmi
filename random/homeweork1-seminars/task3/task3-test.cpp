#include "task3.cpp"
void testSumNodes() {
    BTree<int> treeA;
    treeA.add(20, "");
    assert(sumNodes(treeA) == 0);
    treeA.add(17, "R");
    treeA.add(18, "L");
    assert(sumNodes(treeA) == 0);
    treeA.add(16, "RL");
    assert(sumNodes(treeA) == 17);
    treeA.add(15, "RLR");
    assert(sumNodes(treeA) == 33);
    treeA.add(16, "RLL");
    assert(sumNodes(treeA) == 17);


}
int main() {
    testSumNodes();
}
