#include <iostream>
#include "task1.cpp"
#include <assert.h>
using namespace std;
void testInterval() {
    BSTree<Interval> tree;
    tree.add(Interval(3, 10)).add(Interval(2, 8)).add(Interval(9, 20));
    assert(findIntervalUnion(tree) == Interval(2, 20));
    tree.add(Interval(0, 0));
    assert(findIntervalUnion(tree) == Interval(0, 20));
    tree.add(Interval(1, 1));
    assert(findIntervalUnion(tree) == Interval(0, 20));
}


int main(){
    testInterval();
    return 0;
}
