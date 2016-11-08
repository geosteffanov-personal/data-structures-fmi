#include <iostream>
#include <assert.h>
#include <string.h>
#include <fstream>
#include <vector>


using namespace std;

template <class T>
using mapFn = T (*)(const T&);

template <class T>
struct Node
{
	Node<T> *left, *right;
	T data;

	Node (const T& d,Node<T> *l, Node<T> *r):
	    left(l),right(r),data(d)
    {
    	makeID();
    }
	Node ():left(NULL),right(NULL)
	{
		makeID();
	}

	int getID() const
	{
		return id;
	}

private:
	int id;

	void makeID ()
	{
		static int maxID = 0;
		maxID++;
    	id = maxID;

	}

};

template <class T>
class BTree
{
private:
	Node<T> *root;
	void simplePrint (Node<T> *subTreeRoot) const;
	bool add (const T& data, const char *trace, Node<T>*&);
	void deleteAll (Node<T> *subTreeRoot);
	bool member (const T&,Node<T> *subTreeRoot) const;
	void map (mapFn<T>,Node<T> *subTreeRoot);

	void dottyPrint (Node<T> *subTreeRoot,ostream& out) const;

	void serialize (Node<T>*, ostream&) const;

	void serializeScheme (Node<T>*,  ostream&) const;

	Node<T>* parseTree (istream &in);

	void listLeaves(Node<T> *subTreeRoot, vector<T>& resultVector) const;
	string findTrace(Node<T> *subTreeRoot, string resultString, const T& element) const;

	void prettyPrint(Node<T> *subTreeRoot, int height) const;

	int size(Node<T>* subTreeRoot) const;

	void findValue(Node<T>* subTreeRoot, const int index, int &current, T*& valueHolder) const;

	Node<T>* parseSchemeTree(istream&);

	void findAtLevel(Node<T>* subTreeRoot, int crrLevel, const int level, vector<T> &resultHolder) const;

	int height(Node<T>* subTreeRoot) const;



public:
	BTree();
	BTree<T>& add (const T& data, const char *trace);

	void deserialize (istream&);

	void deserializeScheme (istream&);

	void simplePrint () const;
	void dottyPrint (ostream&);
	//bool isEmpty();
	bool member (const T&) const;
	
	vector<T> listLeaves() const;

	string findTrace(const T& element) const;

	void prettyPrint() const;

	void map (mapFn<T>);

	void serialize (ostream&)const;

	void serializeScheme (ostream&) const;

	int size() const;

	int height() const;

	T& operator[](const int i) const;

	vector<T> level(int k) const;

	~BTree();

};

template<class T>
void BTree<T>::serialize (Node<T> *subTreeRoot, ostream &out) const
{
	if (subTreeRoot == NULL)
	{
		out << "null ";
		return;
	}

	out << subTreeRoot->data << " ";

	serialize (subTreeRoot->left,out);
	serialize (subTreeRoot->right,out);

}

template<class T>
void BTree<T>::serialize (ostream &out) const
{
	serialize (root,out);
	cout << endl;
}

template <class T>
void BTree<T>::serializeScheme (Node<T>* subTreeRoot, ostream &out) const
{
	if (subTreeRoot == NULL) return;

	out << subTreeRoot->data << " ";

	out << "(";
	serializeScheme(subTreeRoot->left, out);
	out << ") ";

	out << "(";
	serializeScheme(subTreeRoot->right, out);
	out << ")";
}

template <class T>
void BTree<T>::serializeScheme(ostream &out) const
{
	out << "(";
	serializeScheme (root, out);
	out << ")";
	cout << endl;
}

template <class T>
void BTree<T>::deserializeScheme(istream &in) {
	deleteAll(root);

	root = parseSchemeTree(in);
}



template<class T>
void BTree<T>::dottyPrint (ostream &out)
{
	out << "digraph G {" << endl;
	dottyPrint (root, out);
	out << "}" << endl;	
}



template<class T>
void BTree<T>::dottyPrint (Node<T> *subTreeRoot,ostream& out) const
{
	if (subTreeRoot == NULL)
		return;

	out << subTreeRoot->getID() 
	    << "[label=\"" 
	    << subTreeRoot->data 
	    << "\"];" << endl;

	if (subTreeRoot->left != NULL)
		out << subTreeRoot->getID() 
	        <<"->"
	        << subTreeRoot->left->getID()
	        << endl;

	if (subTreeRoot->right != NULL)
		out << subTreeRoot->getID() 
	        <<"->"
	        << subTreeRoot->right->getID()
	        << endl;

	dottyPrint (subTreeRoot->left,out);
	dottyPrint (subTreeRoot->right,out);
}



template<class T>
void BTree<T>::map (mapFn<T> f,Node<T> *subTreeRoot)
{
	if (subTreeRoot == NULL)
		return;

	subTreeRoot->data = f (subTreeRoot->data);
	map (f,subTreeRoot->left);
	map (f,subTreeRoot->right);
}

template<class T>
void BTree<T>::map (mapFn<T>f)
{
	map (f,root);
}


template<class T>
bool BTree<T>::member (const T& x) const
{
	return member (x,root);
}


template<class T>
bool BTree<T>::member (const T& x,Node<T> *subTreeRoot) const
{
	if (subTreeRoot == NULL)
		return false;


	return subTreeRoot->data == x ||
	       member (x,subTreeRoot->left) ||
	       member (x,subTreeRoot->right);


}


template<class T>
void BTree<T>::deleteAll (Node<T> *subTreeRoot)
{
	if (subTreeRoot == NULL)
		return;

	deleteAll (subTreeRoot->left);
	deleteAll (subTreeRoot->right);
	delete subTreeRoot;
}

template <class T>
BTree<T>::~BTree()
{
	deleteAll (root);

}


template <class T>
BTree<T>& BTree<T>::add(const T& x, const char *trace)
{
   add (x,trace,root);
   return *this;
}


template <class T>
bool BTree<T>::add(const T& x, const char *trace, Node<T>* &subTreeRoot)
{
	if (subTreeRoot == NULL)
	{
		assert (strlen(trace) == 0);
		subTreeRoot = new Node<T> (x,NULL,NULL);
		return true;
	}

	assert (strlen(trace)>0);

	if (trace[0]=='L')
		return add (x,trace+1,subTreeRoot->left);

	assert (trace[0]=='R');
	return add (x,trace+1,subTreeRoot->right);

	return true;

}

template <class T>
BTree<T>::BTree ():root(NULL){}

template <class T>
void BTree<T>::simplePrint() const
{
	simplePrint (root);
	cout << endl;
}

template <class T>
void BTree<T>::simplePrint(Node<T> *subTreeRoot) const
{
	if (subTreeRoot == NULL)
		return;

	cout << subTreeRoot->data << " ";
	simplePrint (subTreeRoot->left);
	simplePrint (subTreeRoot->right);
}

void removeWhite (istream &in)
{
	while (in.peek() <= 32)
		in.get();
}

template <class T>
Node<T>* BTree<T>::parseTree (istream &in)
{
	
	removeWhite (in);

	if (in.peek() == 'n')
	{
		string dummy;
		in >> dummy;
		assert (dummy == "null");
		return NULL;
	}

	T data;
	in >> data;

	return new Node<T> (data,
		 				parseTree(in),
		 				parseTree(in));


}


template <class T>
Node<T>* BTree<T>::parseSchemeTree (istream &in)
{
	removeWhite(in);
	if (in.peek() == '(') {
		in.get();
		if (in.peek() == ')')
			return NULL;
		T data;
		in >> data;
		removeWhite(in);
		return new Node<T> (data, parseSchemeTree(in), parseSchemeTree(in));
	}

}

template <class T>
void BTree<T>::deserialize (istream &in)
{
	deleteAll(root);

	root = parseTree (in);


}


template <class T>
void BTree<T>::listLeaves(Node<T> *subTreeRoot, vector<T> &resultVector) const {
	if (subTreeRoot ==  NULL)
		return;
	bool alreadyExists = false;
	for (int i = 0; i < resultVector.size(); i++) {
		if(resultVector[i] == subTreeRoot->data) {
			alreadyExists = true;
			break;
		}
	}
	if (!alreadyExists)  {
		resultVector.push_back(subTreeRoot->data);	
	}
	
	listLeaves(subTreeRoot->left, resultVector);
	listLeaves(subTreeRoot->right, resultVector);
}

template <class T>
vector<T> BTree<T>::listLeaves() const {
	vector<T> resultVector;
	listLeaves(root, resultVector);
	return resultVector;
}

template <class T>
string BTree<T>::findTrace(Node<T> *subTreeRoot, string resultString, const T& element) const
{
	if(subTreeRoot == NULL) {
		return "_";
	}
	
	if(subTreeRoot->data == element) {
		return resultString;
	}

	string toTheLeft(resultString);
	string toTheRight(resultString);
	toTheLeft.push_back('L');
	toTheRight.push_back('R');

	string resultLeft(findTrace(subTreeRoot->left, toTheLeft, element));


	string resultRight(findTrace(subTreeRoot->right, toTheRight, element));

	if (resultLeft !=  "_") return resultLeft;
	if (resultRight != "_") return resultRight;
	
	return "_";
}

template <class T>
string BTree<T>::findTrace(const T& element) const 
{
	return findTrace(root, "", element);
}


template <class T>
void BTree<T>::prettyPrint(Node<T>* subTreeRoot, int height) const
{
	if(subTreeRoot == NULL) {
		return;
	}

	prettyPrint(subTreeRoot->right, height + 1);
	
	for (int i = 0; i <= height; i++) {
		cout << "   ";
	}
	cout << subTreeRoot->data << endl;

	prettyPrint(subTreeRoot->left, height + 1);

	return;
}

template <class T>
void BTree<T>::prettyPrint() const
{
	prettyPrint(root, 0);
}

template <class T>
int BTree<T>::size() const
{
	return size(root);
}

template <class T>
int BTree<T>::size(Node<T>* subTreeRoot) const
{
	if(subTreeRoot == NULL)
		return 0;

	return 1 + size(subTreeRoot->left) + size(subTreeRoot->right);

}

template <class T>
int BTree<T>::height(Node<T>* subTreeRoot) const {
	if (subTreeRoot == NULL)
		return 0;

	int leftHeight = size(subTreeRoot->left);
	int rightHeight = size(subTreeRoot->left);
	int maxHeight;
	if (leftHeight < rightHeight) {
		maxHeight = rightHeight;
	} else {
		maxHeight = leftHeight;
	}

	return 1 + maxHeight;
}

template <class T>
int BTree<T>::height() const {
	return height(root);
}

template <class T>
T& BTree<T>::operator[](const int i) const
{
	assert(i < size() && i >= 0 && size() > 0);
	int index = -1;
	T* valueHolder = NULL;
	findValue(root, i, index, valueHolder);
	return *valueHolder;
}

template <class T>
void BTree<T>::findValue(Node<T>* subTreeRoot, const int index, int &current, T*& valueHolder) const 
{
	if (subTreeRoot == NULL) {
		return;
	}
	cout << "DATA:" << subTreeRoot->data << endl;
	current++;
	if (index == current) {
		valueHolder = &subTreeRoot->data;
		return;
	}

	findValue(subTreeRoot->left, index, current, valueHolder);
	if (valueHolder != NULL)
		return;
	findValue(subTreeRoot->right, index, current, valueHolder);
	if (valueHolder != NULL)
		return;
}


template <class T>
void BTree<T>::findAtLevel(Node<T>* subTreeRoot, int crrLevel, const int level, vector<T> &resultHolder) const {
	if (subTreeRoot == NULL)
		return;
	crrLevel++;
	if (crrLevel == level) {
		resultHolder.push_back(subTreeRoot->data);
		return;
	}
	findAtLevel(subTreeRoot->left, crrLevel, level, resultHolder);
	findAtLevel(subTreeRoot->right, crrLevel, level, resultHolder);
}

template <class T>
vector<T> BTree<T>::level(int k) const {
	assert(k < height());
	vector<T> result;
	int crrLevel = -1;
	findAtLevel(root, crrLevel, k, result);
	return result;
}


void testMember ()
{
	BTree<int> t;

	t.add(10,"").add(12,"L").add(14,"R").add(15,"LR");	

	assert (t.member(12) == true);
	assert (t.member(18) == false);
	assert (t.member(15) == true);
}

void testListLeaves ()
{

	cout << "Testing 'listLeaves'" << endl;
	BTree<int> t;
	t.add(10,"").add(12,"L").add(14,"R").add(15,"LR").add(14, "LL").add(12, "RL");
	vector<int> resultVector = t.listLeaves();
	for (int i = 0; i < resultVector.size(); i++) {
		cout << resultVector[i] << endl;
	}
}


void testFindTrace ()
{
	cout << "Testing 'findTrace'" << endl;
	BTree<int> t;
	t.add(10,"").add(12,"L").add(14,"R").add(15,"LR").add(14, "LL").add(12, "RL");
	cout << t.findTrace(15) << endl;
}

void testPrettyPrint()
{
	cout << "Testing pretty 'print'" << endl;
	BTree<int> t;
	t.add(10,"").add(12,"L").add(14,"R").add(15,"LR").add(14, "LL").add(12, "RL");
	t.prettyPrint();
}

void testIndexOperator() {
	cout << "Testing operator [] " << endl;
	BTree<int> t;
	t.add(10,"").add(12,"L").add(14,"R").add(15,"LR").add(14, "LL").add(12, "RL").add(17, "RLL");
	cout << t[6] << endl;
}

void testSize()
{
	cout << "Testing 'size()' " << endl;
	BTree<int> t;
	t.add(10,"").add(12,"L").add(14,"R").add(15,"LR").add(14, "LL").add(12, "RL").add(17, "RLL");
	cout  << "size - " << t.size() << endl;
}

void testSerializeScheme() {

	cout << "Testing 'serializeScheme' " << endl;
	BTree<int> t;
	t.add(10,"").add(12,"L").add(14,"R").add(15,"LR");
	t.serializeScheme(cout);
}

void testDeserializeScheme() {
	BTree<int> test;
	ifstream in ("data.txt");

	test.deserializeScheme (in);
	cout << "---DESERIALIZED TREE-------" << endl;
	test.serializeScheme(cout);

}

void testLevel() {
	cout << "Testing 'level' " << endl;
	BTree<int> test;
	test.add(10,"").add(12,"L").add(14,"R").add(15,"LR");
	vector<int> result = test.level(1);
	for (int i = 0; i < result.size(); i++) {
		cout << result[i] << endl;
	}
}

void testHeight() {
	cout << "Testing 'height()' " << endl;
	BTree<int> test;
	test.add(10,"").add(12,"L").add(14,"R").add(15,"LR");
	cout << test.height() << endl;
}

int plusOne (const int& i)
{
	return i + 1;
}



int main ()
{
	
	// testMember ();

	// BTree<int> t;

	// t.add(10,"").add(12,"L").add(14,"R").add(15,"LR");
	// t.simplePrint();

	// t.map (plusOne);


	// t.simplePrint ();
	// //t.dottyPrint (cerr);

	// cout << "------------" << endl;
	// t.serialize (cout);
	// test.dottyPrint (cerr);
	// testListLeaves();
	// testFindTrace();
	// testPrettyPrint();
	// testIndexOperator();
	// testSerializeScheme();
	// testHeight();
	testLevel();

	return 0;
}