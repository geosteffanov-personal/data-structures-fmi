#include <iostream>
#include "completeTree.cpp"
#include <queue>
#include <assert.h>
using namespace std;

BSTree<int> antiSymmetric(BSTree<int>& tree) {
    BSTree<int> result;
    iter<int> root = tree.iterator();
    if (root.empty())
        return result;
    queue<iter<int>> helperQ;
    helperQ.push(root);

    while(!helperQ.empty()) {
        iter<int> crr = helperQ.front();
        helperQ.pop();
        result.add(-1 * (*crr));
        iter<int> left = crr.goLeft();
        iter<int> right = crr.goRight();
        if (!left.empty())
            helperQ.push(left);
        if (!right.empty())
            helperQ.push(right);
    }
    return result;
}

/* test */
void testAntiSymmetric() {
    BSTree<int> tree1;
    tree1.add(5);
    tree1.add(3);
    tree1.add(6);
    BSTree<int> tree2 = antiSymmetric(tree1);
    iter<int> iterator = tree2.iterator();
    assert(*iterator == -5);
    iter<int> left = iterator.goLeft();
    iter<int> right = iterator.goRight();
    assert(*left == -6);
    assert(*right == -3);
}

int main() {
    testAntiSymmetric();
}
