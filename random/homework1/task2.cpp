#include <iostream>
#include <assert.h>
#include <queue>
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
};

template <class T>
using iter = typename BSTree<T>::TreeIterator;

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

