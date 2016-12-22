#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;
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
public:
    class TreeIterator
	{

	public:
	    TreeIterator() : current(nullptr) {}

	    TreeIterator(const TreeIterator& other) : current(other.current) {}

	    TreeIterator& operator= (const TreeIterator& other) {
            if (this != &other) {
                current = other.current;
            }
            return *this;
	    }

		TreeIterator (Node<T> *&root) : current(root) {}

		T operator * () const {
            assert(current != nullptr);
            return current->data;
		}

		T& operator * () {
            if (current == nullptr)
                current = new Node<T> (T(),nullptr,nullptr);
            return current->data;
		}

		TreeIterator goLeft () {
            assert(current!= nullptr);
            return TreeIterator(current->left);
		}
		TreeIterator goRight () {
            assert(current != nullptr);
            return TreeIterator(current->right);
		}
		bool empty() const {
            return current == nullptr;
		}

	private:
		Node<T> *&current;
	};
private:
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

    BSTree(const BSTree<T>& other) {
        root = copyTree(other.root);
    }

    BSTree<T>& operator=(const BSTree<T>& other) {
        if (this != &other) {
            deleteTree(root);
            root = copyTree(other.root);
        }
    }

    ~BSTree() {
        deleteTree(root);
    }

    TreeIterator iterator() {
        return TreeIterator(root);
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

template <class T>
using iter = typename BSTree<T>::TreeIterator;

/* tests */
void testBSTreeConsAndDest() {
    BSTree<int> testTree;
}

void testIterator() {
    BSTree<int> tree1;
    tree1.add(5);
    tree1.add(2);
    tree1.add(6);

    iter<int> iterator = tree1.iterator();
    assert(!iterator.empty());
    iter<int> left = iterator.goLeft();
    iter<int> right = iterator.goRight();
    assert(!left.empty());
    assert(!right.empty());
    assert(*iterator == 5);
    assert(*left == 2);
    assert(*right == 6);
    iter<int> leftleft = left.goLeft();
    iter<int> leftright = left.goRight();
    iter<int> rightleft = left.goLeft();
    iter<int> rightright = left.goRight();
    assert(leftleft.empty());
    assert(leftright.empty());
    assert(rightleft.empty());
    assert(rightright.empty());
    *leftleft = 10;
    assert(!leftleft.empty());
    assert(*leftleft == 10);
}
