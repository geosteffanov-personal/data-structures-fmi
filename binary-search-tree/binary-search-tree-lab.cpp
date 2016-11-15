#include <iostream>
#include <fstream>
#include <assert.h>
#include <queue>
#include <vector>
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

    void findAtLevel(Node<T>* subTreeRoot, int crrLevel, const int level, vector<T> &resultHolder) const;

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

        if (subTreeRoot->left == NULL &&
            subTreeRoot->right == NULL &&
            subTreeRoot->data == value) {
            delete subTreeRoot;
            subTreeRoot = NULL;
            return;
        }


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
    void deleteTree(Node<T>*& subTreeRoot) {
        if (subTreeRoot == NULL)
            return;

        deleteTree(subTreeRoot->left);
        deleteTree(subTreeRoot->right);
        Node<T>* temp = subTreeRoot;
        delete temp;

        subTreeRoot = NULL;
    }

    #define EMPTY 0
    #define NONE 1
    #define ONLY_LEFT 2
    #define ONLY_RIGHT 3
    #define BOTH 4

    template <class E>
    int treeFootprint(Node<E>* subTreeRoot) const {
        if (subTreeRoot == NULL)
            return EMPTY;
        if (subTreeRoot->left == NULL && subTreeRoot->right == NULL)
            return NONE;
        if (subTreeRoot->left == NULL)
            return ONLY_RIGHT;
        if (subTreeRoot->right == NULL);
            return ONLY_LEFT;
        return BOTH;
    }

    void serializeSorted(Node<T>* subTreeRoot, ofstream& out) {
        if (subTreeRoot == NULL) {
            return;
        }
        serializeSorted(subTreeRoot->left, out);
        out << subTreeRoot->data << "  ";
        serializeSorted(subTreeRoot->right, out);
    }

    void serializeInBinary(Node<int>* subTreeRoot, ofstream &out) {
        if (subTreeRoot == NULL) {
            return;
        }
        serializeInBinary(subTreeRoot->left, out);
        out.write((char *)&(subTreeRoot->data), sizeof(int));
        serializeInBinary(subTreeRoot->right, out);
    }

    template <class E>
    bool isomorphicTo(Node<T>* subTreeRoot, Node<E>* subTreeOther) {
        if (subTreeRoot == NULL && subTreeOther == NULL)
            return true;
        if (subTreeRoot == NULL)
            return false;
        if (subTreeOther == NULL)
            return false;
        return (treeFootprint(subTreeRoot) == treeFootprint(subTreeOther)) &&
                isomorphicTo(subTreeRoot->left, subTreeOther->left) &&
                isomorphicTo(subTreeRoot->right, subTreeOther->right);
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

    template <class E>
    bool isomorphicTo(BSTree<E>& other) {
        return isomorphicTo(root, other.getRoot());
    }

    void serializeSorted(ofstream& out) {
        serializeSorted(root, out);
    }


    void serializeInBinary(ofstream &out) {
        serializeInBinary(root, out);
    }

    void deserializeFromStream(ifstream& in) {
        deleteTree(root);
        int number;
        while(!in.eof()) {
            in.read((char *) &number, sizeof(int));
            add(number);
        }
    }

    void binarySort(const ofstream& out, const istream& in) {
       deserializeFromStream(in);
       serializeSorted(root, out);
    }

    vector<T> level(int k) const;

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

    Node<T>* getRoot() {
        return root;
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
    }
};

template <class T>
void BSTree<T>::findAtLevel(Node<T>* subTreeRoot, int crrLevel, const int level, vector<T> &resultHolder) const {
	if (subTreeRoot == NULL)
		return;
	if (crrLevel == level) {
        bool contains = false;
        for (int i = 0; i < resultHolder.size(); i++) {
            if(resultHolder[i] == subTreeRoot->data)
                contains = true;
        }
		if(!contains)
            resultHolder.push_back(subTreeRoot->data);
		return;
	}
	findAtLevel(subTreeRoot->left, crrLevel + 1, level, resultHolder);
	findAtLevel(subTreeRoot->right, crrLevel + 1, level, resultHolder);
}

template <class T>
vector<T> BSTree<T>::level(int k) const {
	//assert(k < height());
	vector<T> result;
	findAtLevel(root, 0, k, result);
	return result;
}

void testAdd()  {
    BSTree<int> tree;
    tree.add(5).add(3).add(2).add(10).add(11)
       .add(10).add(1).add(12).add(6);
}

void testBFSPrint() {
        BSTree<int> tree;
        tree.add(5).add(3).add(2).add(10).add(11)
            .add(10).add(1).add(12).add(6);
        tree.printBFS();
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
    tree.deleteElement(5);
    assert(tree.maxElem() == 12);
}

void testLevel() {
        BSTree<int> tree;
        tree.add(5).add(3).add(2).add(10).add(11)
            .add(10).add(1).add(12).add(6);

        vector<int> level = tree.level(1);
        vector<int> assertVect;
        assertVect.push_back(3);
        assertVect.push_back(10);

        for (int i = 0; i < level.size(); i++) {
            assert(level[i] == assertVect[i]);
        }

}

void testSerializeSorted() {
    BSTree<int> tree;

    ifstream binaryFileDeser;
    binaryFileDeser.open("bintree.bin", ios::binary );
    tree.deserializeFromStream(binaryFileDeser);

    ofstream result;
    result.open("output.txt");
    tree.serializeSorted(result);
    result.close();

}

void testIsomorphic() {
    BSTree<int> first;
    BSTree<char> second;
    first.add(5);
    first.add(3);
    first.add(6);

    second.add('b');
    second.add('a');
    second.add('c');

    assert(first.isomorphicTo(second));
}

int main() {
    testMax();
    testMin();
    testRemove();
    testLevel();
    testSerializeSorted();
    testIsomorphic();
    return 0;
}
