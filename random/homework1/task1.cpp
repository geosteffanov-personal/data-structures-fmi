#include <iostream>
#include "completeTree.cpp"
#include <queue>
using namespace std;
struct Interval {
        double a;
        double b;

        Interval() {
            a = 0;
            b = 0;
        }
        Interval(double _a, double _b) : a(_a), b(_b) {}
        double getMeasure() const {
            return b - a;
        }

        bool operator < (const Interval& other) const {
            return (b - a) < (other.b - other.a);
        }
        bool operator <= (const Interval& other) const {
            return (b - a) <= (other.b - other.a);
        }
        bool operator == (const Interval& other) const {
            return (b-a) == (other.b - other.a);
        }
        bool operator > (const Interval& other) const {
            return (b-a) > (other.b - other.a);
        }
        bool operator >= (const Interval& other) const {
            return (b-a) >= (other.b - other.a);
        }
    };

ostream& operator << (ostream& os, const Interval& interval) {
    os << "[" << interval.a << ", " << interval.b << "]";
    return os;
}

Interval findIntervalUnion(BSTree<Interval>& tree) {
    queue<iter<Interval>> helperQ;
    iter<Interval> root = tree.iterator();
    if (root.empty())
        return Interval();
    double min = (*root).a;
    double max = (*root).b;
    helperQ.push(root);
    while(!helperQ.empty()) {
        iter<Interval> crr = helperQ.front();
        helperQ.pop();
        iter<Interval> left = crr.goLeft();
        iter<Interval> right = crr.goRight();
        if(!left.empty())
            helperQ.push(left);
        if (!right.empty())
            helperQ.push(right);

        if ((*crr).a < min)
            min = (*crr).a;
        if ((*crr).b > max)
            max = (*crr).b;
    }

    return Interval(min, max);
}

void testInterval() {
    BSTree<Interval> tree;
    tree.add(Interval(3, 5));
    tree.add(Interval(4, 5));
    tree.add(Interval(2, 3));
    tree.add(Interval(8, 16));
    Interval result = findIntervalUnion(tree);
    assert(result == Interval(2, 16));
}

int main() {
    testInterval();
}
