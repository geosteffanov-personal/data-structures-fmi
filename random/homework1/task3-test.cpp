#include <iostream>
#include "task3.cpp"
#include <assert.h>
using namespace std;
void testValues() {
    BTree<digit> tree;
    tree.add(9, "").add(8, "R").add(9, "L").add(2, "LR").add(1, "RL").add(7, "RR");
    stack<digit> digStack = value(tree);
    stack<digit> expected;
    expected.push(9);
    expected.push(2);
    expected.push(9);
    expected.push(1);
    expected.push(8);
    expected.push(7);
    assert(expected == digStack);
}
void testSumDigits() {
    BTree<digit> tree1;
    BTree<digit> tree2;
    tree1.add(0, "").add(0, "R").add(0, "RR").add(1, "RRR");
    tree2.add(0, "").add(0, "R").add(0, "RR").add(2, "RRR");
    stack<digit> sum = sumStack(tree1, tree2);
    stack<digit> expected;
    expected.push(0);expected.push(0);expected.push(0);expected.push(3);
    assert(expected == sum);
    BTree<digit> tree3;
    BTree<digit> tree4;
    tree3.add(9, "").add(9, "R").add(9, "RR").add(9, "RRR");
    tree4.add(1, "");
    stack<digit> sum2 = sumStack(tree3, tree4);
    stack<digit> expected2;
    expected2.push(0);expected2.push(0);expected2.push(0);expected2.push(0);expected2.push(1);
    assert(sum2 == expected2);
}
void testSumDigitsFinal() {
    BTree<digit> tree3;
    BTree<digit> tree4;
    tree3.add(9, "").add(9, "R").add(9, "RR").add(9, "RRR");
    tree4.add(1, "");
    stack<digit> sum2 = sumStack(tree3, tree4);
    stack<digit> expected2;
    expected2.push(0);expected2.push(0);expected2.push(0);expected2.push(0);expected2.push(1);
    assert(sum2 == expected2);
    assert(sumDigitTrees(tree3, tree4) == 0);
}
int main(){
    testValues();
    testSumDigits();
    testSumDigitsFinal();
    return 0;
}
