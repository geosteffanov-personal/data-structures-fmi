#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;

template <typename T>
struct Node {
    T data;
    Node<T>* left;
    Node<T>* right;

    Node() {
        this->data = T();
        right = NULL;
        left = NULL;
    }

    Node(const T data) {
        this->data = data;
        right = NULL;
        left = NULL;
    }

    Node(T d, Node<T>* l, Node<T>* r) :
         data(d), left(l), right(r) {}
};

template <class T>
class BSTree  {
    Node<T>* root;

     void add(Node<T>*& subTreeRoot,const T& element) {
        if(subTreeRoot == NULL) {
            subTreeRoot = new Node<T>(element);
            return;
        }
        if (element <= subTreeRoot->data) {
            add(subTreeRoot->left, element);
            return;
        }
        add(subTreeRoot->right, element);
    }

    void allLevels(Node<T>* subTreeRoot, int height, vector<vector<T>>& result) {
        if (subTreeRoot == NULL) {
            return;
        }

        if (result.size() < height) {
            vector<T> thisLevel;
            thisLevel.push_back(subTreeRoot->data);
            result.push_back(thisLevel);
        } else {
            result[height - 1].push_back(subTreeRoot->data);
        }

        allLevels(subTreeRoot->left, height + 1, result);
        allLevels(subTreeRoot->right, height + 1, result);
    }

public:
    BSTree() {
        root = NULL;
    }

    BSTree<T>& add(const T& element) {
        add(root, element);
        return *this;
    }
    vector<vector<T>> allLevels() {
        vector<vector<T>> result;
        allLevels(root, 1, result);

        return result;
    }
};

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

void testIntervalTree() {
    BSTree<Interval> tree;
    tree.add(Interval(3, 8));
    tree.add(Interval(2, 4));
    tree.add(Interval(3, 10));
    tree.add(Interval(-2, 2));
    tree.add(Interval(-2, 4));
    tree.add(Interval(-6, 3));
    vector<vector<Interval>> levels = tree.allLevels();
    int min = levels[0][0].a;
    int max = levels[0][0].b;
    for (int i = 0; i < levels.size(); i++) {
        for (int j = 0; j < levels[i].size(); j++) {
            if (min > levels[i][j].a) {
                min = levels[i][j].a;
            }
            if (max < levels[i][j].b){
                max = levels[i][j].b;
            }
        }
    }
    Interval result(min, max);
    assert(result == Interval(-6, 10));
}

int main() {
    testIntervalTree();
}
