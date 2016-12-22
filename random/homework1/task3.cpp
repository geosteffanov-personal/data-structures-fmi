#include <iostream>
#include <cstring>
#include <stack>
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
class BTree  {
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

    void add (const T& x, const char *trace, Node<T>* &subTreeRoot) {
        if (subTreeRoot == nullptr)
        {
            assert (strlen(trace) == 0);
            subTreeRoot = new Node<T>(x,nullptr,nullptr);
            return;
        }

        assert (strlen(trace)>0);

        if (trace[0]=='L') {
            add (x,trace+1,subTreeRoot->left);
            return;
        }

        assert (trace[0]=='R');
        add (x,trace+1,subTreeRoot->right);
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
    BTree() {
        root = NULL;
    }

    BTree(const BTree<T>& other) {
        root = copyTree(other.root);
    }

    BTree<T>& operator=(const BTree<T>& other) {
        if (this != &other) {
            deleteTree(root);
            root = copyTree(other.root);
        }
    }

    ~BTree() {
        deleteTree(root);
    }

    TreeIterator iterator() {
        return TreeIterator(root);
    }

    BTree<T>& add(const T& x, const char *trace) {
            add (x,trace,root);
            return *this;
    }
};

template <class T>
using iter = typename BTree<T>::TreeIterator;

int pow10(int exponent) {
    int result = 1;
    for (int i = 0; i < exponent; i++)
        result *= 10;
    return result;
}
#define CALCULATE 0
#define TRAVERSE 1
int value(BTree<int>& tree) {
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
int sumOfDigitTrees(BTree<int>&first, BTree<int> &second) {
    return value(first) + value(second);
}
