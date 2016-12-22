#include <iostream>
#include "completeTree.cpp"
#include <stack>
#include <assert.h>
using namespace std;
int pow10(int exponent) {
    int result = 1;
    for (int i = 0; i < exponent; i++)
        result *= 10;
    return result;
}
#define CALCULATE 0
#define TRAVERSE 1
int value(BSTree<int>& tree) {
    struct Frame {
        iter<int> root;
        int opCode;
        int value;
        Frame(int _op, int _val, iter<int> _r) : opCode(_op), value(_val), root(_r) {}
        Frame(const Frame& other) : root(other.root), opCode(other.opCode), value(other.value) {}
    };

    iter<int> root = tree.iterator();
    if (root.empty())
        return 0;

    int result = 0;
    int exponent = 0;

    stack<Frame> treeSt;
    Frame first(TRAVERSE, -1, root);
    first.opCode = 1;
    first.root = root;

    treeSt.push(first);
    while (!treeSt.empty()) {
        Frame crr = treeSt.top();
        treeSt.pop();
        if (crr.opCode == TRAVERSE) {
            iter<int> crrRoot = crr.root;
            iter<int> left = crrRoot.goLeft();
            iter<int> right = crrRoot.goRight();

            if (!right.empty()) {
                Frame rightTraverse(TRAVERSE, -1, right);
                treeSt.push(rightTraverse);
            }

            Frame calculate(CALCULATE, *crrRoot, tree.iterator());
            treeSt.push(calculate);

            if (!left.empty()) {
                Frame leftTraverse(TRAVERSE, -1,left);
                treeSt.push(leftTraverse);
            }
        } else {
            assert(crr.opCode == CALCULATE);
            int crrDigit = crr.value;
            int toAdd = crrDigit * pow10(exponent);
            exponent++;
            result += toAdd;
        }
    }

    return result;
}
/* test value */
void testValue() {
    BSTree<int> tree1;
    tree1.add(3);
    tree1.add(2);
    tree1.add(4);
    BSTree<int> tree2;
    tree2.add(4);
    tree2.add(4);
    tree2.add(4);
    BSTree<int> tree3;
    tree3.add(9);
    tree3.add(6);
    tree3.add(5);
    tree3.add(6);
    assert(tree1.value == 432);
    assert(tree2.value == 444);
    assert(tree3.value == 9665)
}

int main() {
    testValue();

}
