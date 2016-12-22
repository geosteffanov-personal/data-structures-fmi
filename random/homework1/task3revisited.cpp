#include <iostream>
#include <assert.h>
int pow10(int exponent) {
  int res = 1;
  for (int i = 0; i < exponent; i++) {
    res *= 10;
  }
  return res;
}

template <class T>
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

    int value(Node<T>* subtree, int& power) {
        if (subtree == nullptr)
            return 0;
        int rightVal = value(subtree->right, power);

        power++;
        int crrVal = subtree->data * pow10(power);
        int leftVal = value(subtree->left, power);
        return rightVal + crrVal + leftVal;
    }

    Node<T>* copyTree(Node<T>* other) {
        if (other == nullptr)
            return nullptr;
        return new Node<T>(other->data, copyTree(other->left), copyTree(other->right));
    }

    void deleteTree(Node<T>*& subTreeRoot) {
        if (subTreeRoot == NULL)
            return;

        deleteTree(subTreeRoot->left);
        deleteTree(subTreeRoot->right);
        Node<T>* temp = subTreeRoot;
        delete temp;

        subTreeRoot = NULL;
    }

public:
    BSTree() {
        root = NULL;
    }

    BSTree(const BSTree<T>& other) {
        root = copyTree(other);
    }

    BSTree<T>& operator=(const BSTree<T>& other) {
        if (this != &other) {
            deleteTree(root);
            root = copyTree(other);
        }
    }

    ~BSTree() {
        deleteTree(root);
    }

    BSTree<T>& add(const T& element) {
        add(root, element);
        return *this;
    }

    int value() {
        int power = -1;
        return value(root, power);
}
};

void testValue() {
    BSTree<int> tree;
    tree.add(2);
    tree.add(3);
    tree.add(4);
    tree.add(9);
    tree.add(1);
    assert(tree.value() == 12349);
}
int main() {
    testValue();
}
