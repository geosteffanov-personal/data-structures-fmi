#include<iostream>
#include<assert.h>
#include<queue>
using namespace std;
template <typename T>
struct Node {
    T data;
    Node<T>* left;
    Node<T>* right;

    Node(const T data) {
        this->data = data;
        right = NULL;
        left = NULL;

    }
};

template <typename T>
class BSTree {
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

    void print (Node<T>* subTreeRoot) const {
        if (subTreeRoot == NULL) {
            return;
        }
        print(subTreeRoot->left);
        cout << subTreeRoot->data << " ";
        print(subTreeRoot->right);
    }

    void deleteElement(Node<T>*& subTreeRoot, const T value) {
        if (subTreeRoot == NULL) {
            return;
        }
        // трием от листенце
        if (subTreeRoot->left == NULL &&
            subTreeRoot->right == NULL &&
            subTreeRoot->data == value) {
            delete subTreeRoot;
            subTreeRoot = NULL;
            return;
        }

        // сега лявото е нъл
        if (subTreeRoot->left == NULL && subTreeRoot->data == value) {
            T smallestValue = minElem(subTreeRoot->right);
            subTreeRoot->data = smallestValue;
            deleteElement(subTreeRoot->right, smallestValue);
            return;
        }

        if (subTreeRoot->right == NULL && subTreeRoot->data == value) {
            T largestValue = maxElem(subTreeRoot->left);
            subTreeRoot->data = largestValue;
            deleteElement(subTreeRoot->left, largestValue);
            return;
        }
        if (value < subTreeRoot->data) {
            deleteElement(subTreeRoot->left, value);
            return;
        }
        if (value > subTreeRoot->data) {
            deleteElement(subTreeRoot->right, value);
            return;
        }

        if (value == subTreeRoot->data) {
            T largestValue = maxElem(subTreeRoot->left);
            subTreeRoot->data = largestValue;
            deleteElement(subTreeRoot->left, largestValue);
            return;
        }
        return;
    }
    void deleteTree(Node<T>* subTreeRoot) {
        if (subTreeRoot == NULL)
            return;

        deleteTree(subTreeRoot->left);
        deleteTree(subTreeRoot->right);
        delete subTreeRoot;
    }



    public:

    BSTree()  {
        root = NULL;
    }

    BSTree<T>& add(const T& element) {
        add(root, element);
        return *this;
    }

    void print() const {
        print(root);
    }

     void printBFS() const {
        if (root == NULL)
            return;
        Node<T>* currentNode = root;
        queue<Node<T>*> elementHolder;
        elementHolder.push(currentNode);
        while(!elementHolder.empty())
        {
            currentNode = elementHolder.front();
            cout << currentNode->data << " ";
            elementHolder.pop();
            if (currentNode->left != NULL) {
                elementHolder.push(currentNode->left);
            }
            if (currentNode->right != NULL) {
                elementHolder.push(currentNode->right);
            }
        }

    }


    void deleteElement(const T value) {
        deleteElement(root, value);
    }

    T minElem(Node<T>* currentRoot) const {
        assert(root != NULL);
        while (currentRoot->left != NULL) {

            currentRoot = currentRoot->left;
        }

        return currentRoot->data;

    }

    T maxElem(Node<T>* currentRoot) const {
        assert(root != NULL);
        while (currentRoot->right != NULL) {

            currentRoot = currentRoot->right;
        }

        return currentRoot->data;
    }

    T maxElem(){
        return maxElem(root);
    }
    T minElem() {
        return minElem(root);
    }

    ~BSTree() {
        deleteTree(root);
        root = NULL;
    }
};

void testAdd()  {
    BSTree<int> tree;
    tree.add(5).add(3).add(2).add(10).add(11)
       .add(10).add(1).add(12).add(6);
    tree.print();
}

void testBFSPrint() {
        BSTree<int> tree;
        tree.add(5).add(3).add(2).add(10).add(11)
            .add(10).add(1).add(12).add(6);
        tree.printBFS();

        /*
              5
            3   10
           2  10  11
          1  6     12

        */
}

void testMin() {
       BSTree<int> tree;
        tree.add(5).add(3).add(2).add(10).add(11)
            .add(10).add(1).add(12).add(6);

    assert(tree.minElem() == 1);
}

void testMax() {
    BSTree<int> tree;
        tree.add(5).add(3).add(2).add(10).add(11)
            .add(10).add(1).add(12).add(6);

    assert(tree.maxElem() == 12);

}

void testRemove() {
    BSTree<int> tree;
        tree.add(5).add(3).add(2).add(10).add(11)
            .add(10).add(1).add(12).add(6);
    tree.print();
    cout << "\n\n";
    tree.deleteElement(5);
    assert(tree.maxElem() == 12);
    tree.print();


}

int main() {
    testMax();
    testMin();
    testRemove();
    return 0;
}
