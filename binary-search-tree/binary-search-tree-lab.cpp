#include <iostream>
#include <fstream>
#include <assert.h>
#include <queue>
#include <cmath>
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

    bool member(Node<T>* subTreeRoot, const T& element) const {
        if (subTreeRoot == nullptr)
            return false;
        if (subTreeRoot->data == element)
            return true;
        if (subTreeRoot->data >= element) {
            return member(subTreeRoot->left, element);
        }
        return member(subTreeRoot->right, element);

    }

    void findAllPaths(Node<T>* subTreeRoot, vector<T> &currPath, vector<vector<T>> &allPaths) {
        if (subTreeRoot == NULL){
            cout << "NULL" << endl;
            return;
        }
        currPath.push_back(subTreeRoot->data);
        if (subTreeRoot->left == NULL && subTreeRoot->right == NULL) {
            allPaths.push_back(currPath);
        } else {
            findAllPaths(subTreeRoot->left, currPath, allPaths);
            findAllPaths(subTreeRoot->right, currPath, allPaths);
        }
        currPath.pop_back();
    }

    int size(Node<T>* subTreeRoot) const {
        if (subTreeRoot == nullptr)
            return 0;

        return 1 + size(subTreeRoot->left) + size(subTreeRoot->right);
    }

    bool isBalanced(Node<T>* subTreeRoot) const {
        if (subTreeRoot == nullptr) {
            return true;
        }
        return (abs(size(subTreeRoot->left) - size(subTreeRoot->right)) <= 1) &&
                isBalanced(subTreeRoot->left) && isBalanced(subTreeRoot->right);
    }

    T sameParent(Node<T>* subTreeRoot, T firstElem, T secondElem) {
        bool firstIsMemberLeft = member(subTreeRoot->left, firstElem);
        bool secondIsMemberRight = member(subTreeRoot->right, secondElem);

        bool firstIsMemberRight = member(subTreeRoot->right, firstElem);
        bool secondIsMemberLeft = member(subTreeRoot->left, secondElem);

        if ((firstIsMemberLeft && secondIsMemberRight) ||
            (firstIsMemberRight && secondIsMemberLeft))
            return subTreeRoot->data;


        else if (firstIsMemberLeft) {
                /* dwete sa left memberi */
                if ((subTreeRoot->left->data == firstElem) ||
                    (subTreeRoot->left->data == secondElem))
                     return subTreeRoot->data;


                 return sameParent(subTreeRoot->left, firstElem, secondElem);
        } else {
            /* dwete sa right memberi */
            if ((subTreeRoot->right->data == firstElem) ||
                (subTreeRoot->right->data == secondElem))
                return subTreeRoot->data;

                return sameParent(subTreeRoot->right, firstElem, secondElem);
        }
    }

    void getPath(Node<T>* subTreeRoot, const T element, vector<T>& path) const {
        path.push_back(subTreeRoot->data);
        if (subTreeRoot->data == element) {
            return;
        }
        if (member(subTreeRoot->left, element)) {
            getPath(subTreeRoot->left, element, path);
            return;
        }
        if (member(subTreeRoot->right, element)) {
            getPath(subTreeRoot->right, element, path);
            return;
        }
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

    bool member (const T& element) const {
        return member(root, element);
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

    vector<vector<T>> allPaths() {
        vector<vector<T>> result;
        vector<T> curr;
        findAllPaths(root, curr, result);
        return result;
    }

    bool isBalanced() const {
        return isBalanced(root);
    }

    T sameParent(T firstElem, T secondElem) {
        assert(member(firstElem) && member(secondElem));
        return sameParent(root, firstElem, secondElem);
    }

    vector<T> getPath(const T element) {
        vector<T> result;
        getPath(root, element, result);
        return result;
    }

    int size() const {
        return size(root);
    }
    ~BSTree() {
        deleteTree(root);
    }

    vector<vector<T>> allLevels() {
        vector<vector<T>> result;
        allLevels(root, 1, result);

        return result;
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

void testMember() {
    BSTree<int> tree;
    tree.add(1);
    tree.add(2);
    tree.add(3);
    tree.add(4);
    assert(tree.member(1));
    assert(tree.member(2));
    assert(tree.member(3));
    assert(tree.member(4));
    assert(!tree.member(5));

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

void testAllPaths() {
    BSTree<int> tree;
    tree.add(1);
    tree.add(-1);
    tree.add(2);
    tree.add(3);

    vector<vector<int>> result = tree.allPaths();

    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result[i].size(); j++) {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }
}

void testSize() {
    BSTree<int> tree;
    tree.add(1);
    tree.add(1);
    tree.add(1);
    tree.add(1);
    assert(tree.size() == 4);

}

void sameParent() {
    BSTree<int> tree;
    tree.add(5);
    tree.add(6);
    tree.add(2);
    tree.add (1);
    tree.add(3);
    assert(tree.sameParent(1,3) == 2);
}

void testPath() {
    BSTree<int> tree;
    tree.add(5);
    tree.add(-1);
    tree.add(6);
    tree.add(2);
    tree.add(3);

    vector<int> path = tree.getPath(3);
    assert(path.size() == 4);
    assert(path[0] = 5);
    assert(path[1] = -1);
    assert(path[2] = 2);
    assert(path[3] = 3);
}

void testBalancedTree() {
    BSTree<int> tree;
    tree.add(10);
    tree.add(11);
    tree.add(9);
    assert(tree.isBalanced());

    tree.add(8);
    tree.add(7);
    tree.add(6);
    assert(!tree.isBalanced());

    BSTree<int> tree2;
    tree2.add(5);
    tree2.add(3);
    tree2.add(4);
    tree2.add(20);
    tree2.add(17);
    tree2.add(18);

    assert(!tree2.isBalanced());
}

void testAllLevels() {
    BSTree<int> tree;
    tree.add(5);
    tree.add(3);
    tree.add(4);
    tree.add(20);
    tree.add(17);
    tree.add(18);

    vector<vector<int>> result = tree.allLevels();

    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result[i].size(); j++) {
            cout << " " << result[i][j];
        }
        cout << "\n";
    }

}
int main() {
    testMember();
    testMax();
    testMin();
    testRemove();
    testLevel();
    testSerializeSorted();
    testIsomorphic();
    testAllPaths();
    testSize();
    testBalancedTree();
    sameParent() ;
    testPath();
    testAllLevels();
    return 0;
}
