#include <iostream>
#include <assert.h>
#include <stack>
using namespace std;


template <class T>
class BSTree {
private:
    struct Node {
        Node *left, *right;
        T data;

        Node(const T& d, Node *l = nullptr, Node *r = nullptr);
        int getID() const;

    private:
        int ID;
        void generateID();
    };

    //при обхождането на дървото със стек,
	//в стека се поставят два вида "чакащи операции":
	//"извеждане" на елемента, сочен от указателя,
	//или обхождане на поддървото, сочено от указателя
    using pendingTraverseStep = pair<int, Node*>;

    //всеки указател, попаднал в стека, е
	//"анотиран" с едната от двете операции
    #define STEP_ACCESS_ROOT 0
    #define STEP_TRAVERSE 1
public:
    class LERORIIterator {
    public:
        LERORIIterator (Node *root);
        T& operator * ();
        LERORIIterator& operator ++ ();
        bool operator != (const LERORIIterator &other);

    private:
		/*
		Стек с "изчакващи" операции.
		Празният стек "кодира" край на процеса
		по обхождане.
		*/
		stack<pendingTraverseStep> operations;
		void unwind ();
    };

private:
    Node* root;
    void deleteAll(Node *subtreeRoot);
    void dottyPrint(Node *subtreeRoot, ostream& out) const;
    static Node* copyTree(const Node *subTreeRoot);
    void add(Node *&subTreeRoot, const T& value);
    void deleteElement(Node *& subTreeRoot, const T& value);
    T minelement(Node *subTreeRoot) const;
    bool member(const T& value, Node *subTreeRoot) const;

public:
    BSTree();
    BSTree(const BSTree<T>& other);
    BSTree<T>& operator = (const BSTree<T>& other);
    ~BSTree();

    LERORIIterator end();
    LERORIIterator begin();

    BSTree<T>& add(const T& value);
    void deleteElement(const T& value);
    void dottyPrint(ostream& out) const;

    T minelement ()const;
    bool member(const T& value) const;
};

template <class T>
BSTree<T>::Node::Node (const T& d,BSTree<T>::Node *l, BSTree<T>::Node *r)
  :left(l),right(r),data(d)
{
	generateID();
}

template <class T>
int BSTree<T>::Node::getID() const
{
	return ID;
}

template <class T>
void BSTree<T>::Node::generateID ()
{
	static int maxID = 0;
	maxID++;
	ID = maxID;

}

/*
Обхождането на дървото стартира с поставяне на
операция за обхождане, започвайки от корена на дървото
*/
template<class T>
BSTree<T>::LERORIIterator::LERORIIterator (BSTree<T>::Node *root)
{
    if(root != nullptr) {
        operations.push(BSTree<T>::pendingTraverseStep (STEP_TRAVERSE,root));
        //unwind осигурява, че на върха на стека
        //има операция за извличане или стекът е празен. Други
        //състояния на стека не са допустими.
        unwind();
    }
}

template<class T>
T& BSTree<T>::LERORIIterator::operator * ()
{
	//всички операции с итератора осигуряват, че на върха му
	//има операция за извличане или стекът е празен. Други
	//състояния на стека не са допустими.
	//Възелът на върха на стека е текущо посетения възел
	//при обхождането
	assert (!operations.empty());
	assert (operations.top().first == STEP_ACCESS_ROOT);
	assert (operations.top().second != nullptr);

	return operations.top().second->data;
}
template <class T>
typename BSTree<T>::LERORIIterator& BSTree<T>::LERORIIterator::operator++ ()
{
	//всички операции с итератора осигуряват, че на върха му
	//има операция за извличане или стекът е празен. Други
	//състояния на стека не са допустими.

	assert (!operations.empty());
	//премахва се операцията за извличане, която е на върха на стека.
	//това довежда до продължаване на обхождането към следващите "части"
	//да дървото, или "активиране" на ичакващите под върха на стека операции
	operations.pop();
	//стекът се "доразвива" до достигане на следваща
	//операция за извличане
	unwind();
	return *this;
}

template<class T>
bool BSTree<T>::LERORIIterator::operator != (const LERORIIterator &other)
{

	if (operations.empty())
		return !other.operations.empty();

	if (other.operations.empty())
		return !operations.empty();

	//и двете са непразни

	return operations.top() != other.operations.top();
}

template<class T>
void BSTree<T>::LERORIIterator::unwind ()
{

	//всички операции с итератора осигуряват, че на върха му
	//има операция за извличане или стекът е празен. Други
	//състояния на стека не са допустими.

	//този метод извършва обхождането на чакащите за
	//обхождане указатели към поддървета до момента, в който
	//на върха на стека попадне операция за извличане на елемент. Т.е.
	//обхождането се "развива" до достигане на следващя чакащ
	//за "отпечатване" връх


	if (operations.empty())
		return;

	BSTree<T>::pendingTraverseStep topOperation = operations.top();
	BSTree<T>::Node* topNode = topOperation.second;

	while (!operations.empty() && topOperation.first != STEP_ACCESS_ROOT)
	{

		operations.pop();

		if (topNode->right != nullptr)
			operations.push (BSTree<T>::pendingTraverseStep(STEP_TRAVERSE,topNode->right));
		operations.push (BSTree<T>::pendingTraverseStep(STEP_ACCESS_ROOT,topNode));
		if (topNode->left != nullptr)
			operations.push (BSTree<T>::pendingTraverseStep(STEP_TRAVERSE,topNode->left));

		topOperation = operations.top();
		topNode = topOperation.second;

	}

	//стекът е или празен или на върха му има операция за извличане
}

template<class T>
typename BSTree<T>::LERORIIterator BSTree<T>::end ()
{
	return LERORIIterator (nullptr);
}

template<class T>
typename BSTree<T>::LERORIIterator BSTree<T>::begin ()
{
	return LERORIIterator (root);
}
template<class T>
void BSTree<T>::deleteElement (BSTree<T>::Node *&subTreeRoot, const T&x)
{
	//триене от празно дърво
	if (subTreeRoot==nullptr)
		return;

	//триене от листо
	if (subTreeRoot->data == x &&
		subTreeRoot->left == nullptr &&
		subTreeRoot->right == nullptr)

	{
		delete subTreeRoot;
		subTreeRoot = nullptr;
		return;
	}

	//триене от лявото поддърво
	if (x < subTreeRoot->data)
	{
		deleteElement (subTreeRoot->left,x);
		return;
	}

	//триене от дясното поддърво
	if (x > subTreeRoot->data)
	{
		deleteElement (subTreeRoot->right,x);
		return;
	}

	//вече сме сигурни, че трием корена!
	//освен това сме сигурни, че корена има ПОНЕ ЕДИН
	//наследник

	//триене на корен само с 1 наследник
	if (subTreeRoot->right == nullptr)
	{
		BSTree<T>::Node *tmp = subTreeRoot;
		subTreeRoot = subTreeRoot->left;
		delete tmp;
		return;
	}

	//триене на корен само с 1 наследник
	//този случй може да не се разглежда
	if (subTreeRoot->left == nullptr)
	{
		BSTree<T>::Node *tmp = subTreeRoot;
		subTreeRoot = subTreeRoot->right;
		delete tmp;
		return;
	}


	//триене на корена
	//вече сме сигурни, че корена има точно два наследника
	T minel = minelement(subTreeRoot->right);
	subTreeRoot->data = minel;
	deleteElement (subTreeRoot->right, minel);


}

template<class T>
void BSTree<T>::deleteElement (const T&x)
{
	deleteElement (root,x);
}

template<class T>
T BSTree<T>::minelement (BSTree<T>::Node *subTreeRoot) const
{
	assert (subTreeRoot != nullptr);
	BSTree<T>::Node *current = subTreeRoot;

	while (current->left != nullptr)
	{
		current = current->left;
	}

	return current->data;

}

template<class T>
T BSTree<T>::minelement () const
{
	return minelement (root);

}

template<class T>
BSTree<T>& BSTree<T>::operator = (const BSTree<T> &other)
{
	if (this == &other)
		return *this;

	deleteAll (root);
	root = copyTree (other.root);

	return *this;
}

template<class T>
typename BSTree<T>::Node* BSTree<T>::copyTree (const BSTree<T>::Node *subTreeRoot)
{
	if (subTreeRoot == nullptr)
		return nullptr;

	return new BSTree<T>::Node (subTreeRoot->data,
		                copyTree(subTreeRoot->left),
		                copyTree(subTreeRoot->right));
}

template<class T>
BSTree<T>::BSTree (const BSTree<T> &other)
{
	root = copyTree (other.root);
}

template<class T>
void BSTree<T>::dottyPrint (ostream &out) const
{
	dottyPrint (root,out);
}

template<class T>
void BSTree<T>::dottyPrint (BSTree<T>::Node *subTreeRoot,ostream& out) const
{
	if (subTreeRoot == nullptr)
		return;

	out << subTreeRoot->getID()
	    << "[label=\""
	    << subTreeRoot->data
	    << "\"];" << endl;

	if (subTreeRoot->left != nullptr)
		out << subTreeRoot->getID()
	        <<"->"
	        << subTreeRoot->left->getID()
	        << endl;

	if (subTreeRoot->right != nullptr)
		out << subTreeRoot->getID()
	        <<"->"
	        << subTreeRoot->right->getID()
	        << endl;

	dottyPrint (subTreeRoot->left,out);
	dottyPrint (subTreeRoot->right,out);
}

template<class T>
bool BSTree<T>::member (const T& x,BSTree<T>::Node *subTreeRoot) const
{
	if (subTreeRoot == nullptr)
		return false;


	return subTreeRoot->data == x ||
	       member (x,subTreeRoot->left) ||
	       member (x,subTreeRoot->right);


}
template <class T>
bool BSTree<T>::member(const T& value) const {
    return member(value, root);
}

template<class T>
void BSTree<T>::deleteAll (BSTree<T>::Node *subTreeRoot)
{
	if (subTreeRoot == nullptr)
		return;

	deleteAll (subTreeRoot->left);
	deleteAll (subTreeRoot->right);
	delete subTreeRoot;
}

template <class T>
BSTree<T>::~BSTree()
{
	deleteAll (root);
	root = nullptr;

}
template<class T>
void BSTree<T>::add (BSTree<T>::Node* &subTreeRoot,const T& x)
{

	if (subTreeRoot == nullptr)
	{
		subTreeRoot = new BSTree<T>::Node (x,nullptr,nullptr);
		return;
	}

	if (x <= subTreeRoot->data)
	{
		add (subTreeRoot->left,x);
	} else {
		add (subTreeRoot->right,x);
	}

}


template<class T>
BSTree<T>& BSTree<T>::add (const T& x)
{
	add(root,x);
	return *this;
}


template <class T>
BSTree<T>::BSTree ():root(nullptr){}



