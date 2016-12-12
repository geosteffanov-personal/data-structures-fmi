#include <iostream>
#include <assert.h>
#include <stack>
using namespace std;


template <class T>
class BinTree {
    struct Node {
        T data;
        Node* left, right;

        Node(T);
        Node(T, Node*, Node*);
    };

    class LeftRootRightIterator {
        using pendingTraverseStep = pair<int, Node*>;
        #define TRAVERSE 1
        #define EXTRACT 0

        stack<pendingTraverseStep> opStack;
        void unwind();

    public:
        LeftRootRightIterator(Node* );
        T& operator * ();
        LeftRootRightIterator& operator++();
        bool operator != (const LeftRootRightIterator&);
    };

    class HierarchicalIterator {
        Node *&currentSubtree;
    public:
        T operator * () const;
        T& operator * () ;
        HierarchicalIterator goLeft();
        HierarchicalIterator goRight();
        bool empty();
    };
    private:
    Node* root;
    bool add(const T& data, const char* trace, Node*&);
    void deleteAll(Node*&);

    public:

};
