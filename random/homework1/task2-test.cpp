#include <iostream>
#include "task2.cpp"
#include <assert.h>
using namespace std;
void testAntisymmetric() {
    BSTree<int> tree;
    tree.add(5).add(6).add(7).add(2);
    BSTree<int> result = antiSymmetric(tree);
    iter<int> iterator = result.iterator();
    assert((*iterator) == -5);
    iter<int> left = iterator.goLeft();
    iter<int> right = iterator.goRight();
    assert(!left.empty());
    assert(!right.empty());
    assert((*left) == -6);
    assert((*right) == -2);
    iter<int> rightRight = right.goRight();
    iter<int> rightLeft = right.goLeft();
    assert(rightRight.empty());
    assert(rightLeft.empty());
    iter<int> leftRight = left.goRight();
    iter<int> leftLeft = left.goLeft();
    assert(leftRight.empty());
    assert(!leftLeft.empty());
    assert((*leftLeft) == - 7);
    iter<int> leftLeftLeft = leftLeft.goLeft();
    iter<int> leftLeftRight = leftLeft.goRight();
    assert(leftLeftLeft.empty());
    assert(leftLeftRight.empty());
}

int main(){
    testAntisymmetric();
    return 0;
}
