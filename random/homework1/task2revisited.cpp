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

    Node<T>* antisymmetricTree(Node<T>* subTreeRoot) {
        if (subTreeRoot == nullptr)
            return nullptr;
        return new Node<T>((subTreeRoot->data) * (-1),
                            antisymmetricTree(subTreeRoot->right),
                                antisymmetricTree(subTreeRoot->left));
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

    void print (Node<T>* subTreeRoot) const {
        if (subTreeRoot == NULL) {
            return;
        }
        print(subTreeRoot->left);
        cout << subTreeRoot->data << " ";
        print(subTreeRoot->right);
    }

    bool equal (Node<T>* root, Node<T>* otherRoot) {
        if ((!root && otherRoot) || (!otherRoot && root))
            return false;
        if (!root && !otherRoot)
            return true;
        return (root->data == otherRoot->data) &&
                equal(root->left, otherRoot->left) &&
                equal(root->right, otherRoot->right);
    }

public:
    BSTree() {
        root = NULL;
    }

    BSTree<T>& add(const T& element) {
        add(root, element);
        return *this;
    }


    void antisymmetrize() {
        Node<T>* newRoot = antisymmetricTree(root);
        deleteTree(root);
        root = newRoot;
    }

    void print() const {
        print(root);
    }

    bool equal(BSTree<T>& other) {
        return equal(root, other.root);
    }

};
void checkAntisymmetric() {
    BSTree<int> tree;
    tree.add(15);
    tree.add(1);
    tree.add(5);
    tree.add(16);
    tree.antisymmetrize();
    BSTree<int> negTree;
    negTree.add(-15);
    negTree.add(-1);
    negTree.add(-5);
    negTree.add(-16);

    assert(tree.equal(negTree));
}

int main() {
    checkAntisymmetric();
    return 0;
}



