#include <iostream>
#include "task4.cpp"
using namespace std;
void testReadWord() {
    BTree<char> tree;
    tree.add('r', "");
    tree.add('n', "R");
    tree.add('m', "L");
    tree.add('h', "RL");
    tree.add('e', "RLR");
    tree.add('l', "RLRL");
    tree.add('l', "RLRLL");
    tree.add('m', "RLRLLR");
    tree.add('p', "RLRLLRR");
    tree.add('m', "LR");
    tree.add('m', "LL");
    assert(readWord(tree, "hell"));
    assert(!(readWord(tree, "apple")));
    assert(!(readWord(tree, "rhe")));
}
int main() {
    testReadWord();
}
