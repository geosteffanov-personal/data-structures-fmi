#include <iostream>
#include <assert.h>
#include <string.h>
#include <fstream>
#include <vector>


using namespace std;


template <class T>
using mapFn = T (*)(const T&);

int plusOne (const int& i)
{
	return i + 1;
}

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
    Node<T>* deletedBOT(Node<T>* subTreeRoot, const T& x) const;
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



	static Node<T>* copyTree (const Node<T> *subTreeRoot);

	void insertBOT (Node<T>*&subTreeRoot,const T& x);

	Node<T>* insertedBOT (Node<T>*subTreeRoot, const T& x);

	void deleteElement (Node<T> *&subTreeRoot, const T&x);

	T minelement (Node<T> *subTreeRoot) const;
	T maxelement (Node<T>* subTreeRoot) const;

	bool isBOT(Node<T>* subTreeRoot) const;

public:
	BTree();
	BTree (const BTree<T> &other);

	BTree<T>& operator = (const BTree<T> &other);

	BTree<T>& add (const T& data, const char *trace);

	void deleteElement (const T&x);

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

	BTree<T>& insertBOT (const T& x);

	BTree<T> insertedBOT (const T& x);

	T minelement ()const;

    BTree<T> deletedBOT(const T& x) const;

	~BTree();

	bool hasSameLevels() const;

	T maxelement() const;
	bool isBOT() const;

};

template<class T>
void BTree<T>::deleteElement (Node<T> *&subTreeRoot, const T&x)
{
	//триене от празно дърво
	if (subTreeRoot==NULL)
		return;

	//триене от листо
	if (subTreeRoot->data == x &&
		subTreeRoot->left == NULL &&
		subTreeRoot->right == NULL)

	{
		delete subTreeRoot;
		subTreeRoot = NULL;
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
	if (subTreeRoot->right == NULL)
	{
		Node<T> *tmp = subTreeRoot;
		subTreeRoot = subTreeRoot->left;
		delete tmp;
		return;
	}

	//триене на корен само с 1 наследник
	//този случй може да не се разглежда
	if (subTreeRoot->left == NULL)
	{
		Node<T> *tmp = subTreeRoot;
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
void BTree<T>::deleteElement (const T&x)
{
	deleteElement (root,x);
}

template<class T>
T BTree<T>::minelement (Node<T> *subTreeRoot) const
{
	assert (subTreeRoot != NULL);
	Node<T> *current = subTreeRoot;

	while (current->left != NULL)
	{
		current = current->left;
	}

	return current->data;

}


template<class T>
T BTree<T>::minelement () const
{
	return minelement (root);

}
template <class T>
bool BTree<T>::hasSameLevels() const {
 for (int i = 0; i < height(); i++) {
        for (int j = 0; j < height(); j++) {
            vector<T> firstComparand = level(i);
            vector<T> secondComparand = level(j);
            bool isSubset = true;
            bool isSuperset = true;
            for (int k = 0; k < firstComparand.size(); k++) {
                bool isContained = false;
                for (int l = 0; l < secondComparand.size(); l++) {
                    if (firstComparand[k] == secondComparand[l]) {
                        isContained = true;
                    }
                    if (isContained)
                        break;
                }
                if (!isContained)
                    return false;

            }
            for (int l = 0; l < secondComparand.size(); l++) {
                bool isContained = false;
                for (int k = 0; k < firstComparand.size(); k++) {
                    if (secondComparand[l] == firstComparand[k]) {
                        isContained = true;
                    }
                    if (isContained)
                        break;
                }
                if (!isContained)
                    return false;
            }
            return true;
        }
	 }
}

template<class T>
BTree<T> BTree<T>::insertedBOT (const T& x)
{
	BTree<T> result;
	result.root = insertedBOT (root,x);

	return result;
}
template <class T>
T BTree<T>::maxelement () const {
    return maxelement(root);
}

template <class T>
T BTree<T>::maxelement (Node<T> *subTreeRoot) const
{
	assert (subTreeRoot != NULL);
	Node<T> *current = subTreeRoot;

	while (current->right != NULL)
	{
		current = current->right;
	}
	return current->data;
}


template <class T>
bool BTree<T>::isBOT() const {
    return isBOT(root);
}

template <class T>
bool BTree<T>::isBOT(Node<T>* subTreeRoot) const {
  if (subTreeRoot == NULL) {
    return true;
  }
  if (subTreeRoot->left == NULL && subTreeRoot->right == NULL) {
    return true;
  }
  if (subTreeRoot->left == NULL) {
    return (subTreeRoot->data < minelement(subTreeRoot->right)) &&
            isBOT(subTreeRoot->right);
  }

  if (subTreeRoot->right == NULL) {
        return (subTreeRoot->data >= maxelement(subTreeRoot->right)) &&
                isBOT(subTreeRoot->left);
  }

    return (subTreeRoot->data < minelement(subTreeRoot->right)) &&
           (subTreeRoot->data >= maxelement(subTreeRoot->left)) &&
           isBOT(subTreeRoot->left) && isBOT(subTreeRoot->right);
}

template<class T>
BTree<T> BTree<T>::deletedBOT (const T& x) const {
    BTree<T> result;
    result.root = deletedBOT (root, x);

    return result;

}
template <class T>
Node<T>* BTree<T>::deletedBOT (Node<T>* subTreeRoot, const T& x) const {
    if (subTreeRoot == NULL) {
        return NULL;
    } /* не сме намерили съответния елемент */
    if (subTreeRoot->data == x)  { // опа това трябва да се трие!!
        if (subTreeRoot->left == NULL && subTreeRoot-> right == NULL) {
            return NULL;
        }
        if (subTreeRoot->right != NULL) {
                // right is not null
                T minel = minelement(subTreeRoot->right);
                return new Node<T> (minel, deletedBOT(subTreeRoot->left, minel), deletedBOT(subTreeRoot->right, minel));
        } else { // right is null left is not
            return deletedBOT(subTreeRoot->left, x + 1);
        }
    } else if (x < subTreeRoot->data) {
        return new Node<T> (subTreeRoot->data, deletedBOT(subTreeRoot->left, x),
                        deletedBOT(subTreeRoot->right, x));
    } else {
        return new Node<T> (subTreeRoot->data, deletedBOT(subTreeRoot->left, x),
                        deletedBOT(subTreeRoot->right, x));
    }

}
template<class T>
Node<T>* BTree<T>::insertedBOT (Node<T>*subTreeRoot, const T& x)
{
	if (subTreeRoot == NULL)
	{
		return new Node<T> (x,NULL,NULL);
	}

	if (x > subTreeRoot->data)
	{
		return new Node<T> (subTreeRoot->data,
							copyTree(subTreeRoot->left),
							insertedBOT(subTreeRoot->right,x));

	}

	return new Node<T> (subTreeRoot->data,
						insertedBOT(subTreeRoot->left,x),
						copyTree(subTreeRoot->right));

}




template<class T>
void BTree<T>::insertBOT (Node<T>* &subTreeRoot,const T& x)
{

	if (subTreeRoot == NULL)
	{
		subTreeRoot = new Node<T> (x,NULL,NULL);
		return;
	}

	if (x <= subTreeRoot->data)
	{
		insertBOT (subTreeRoot->left,x);
	} else {
		insertBOT (subTreeRoot->right,x);
	}

}


template<class T>
BTree<T>& BTree<T>::insertBOT (const T& x)
{
	insertBOT (root,x);
	return *this;
}

template<class T>
BTree<T>& BTree<T>::operator = (const BTree<T> &other)
{
	if (this == &other)
		return *this;

	deleteAll (root);
	root = copyTree (other.root);

	return *this;
}


template<class T>
Node<T>* BTree<T>::copyTree (const Node<T> *subTreeRoot)
{
	if (subTreeRoot == NULL)
		return NULL;

	return new Node<T> (subTreeRoot->data,
		                copyTree(subTreeRoot->left),
		                copyTree(subTreeRoot->right));
}

template<class T>
BTree<T>::BTree (const BTree<T> &other)
{
	root = copyTree (other.root);
}


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

	prettyPrint();
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
	root = NULL;

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

	simplePrint (subTreeRoot->left);
	cout << subTreeRoot->data << " ";
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
	cout << "!" << endl;
	if (in.peek() == '(') {
		in.get();
		if (in.peek() == ')') {
            in.get();
            cout << "EMPTY TREE";
            return NULL;
		}
		T data;
		in >> data;
		cout << "DATA: " << data <<endl;
		Node<T>* result =  new Node<T> (data, parseSchemeTree(in), parseSchemeTree(in));
		removeWhite(in);
		if (in.peek() == ')')
            in.get();
        return result;
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

	if (subTreeRoot->left != NULL || subTreeRoot->right != NULL) {
        listLeaves(subTreeRoot->left, resultVector);
        listLeaves(subTreeRoot->right, resultVector);
        return;
	}

    bool alreadyExists = false;
	for (int i = 0; i < resultVector.size(); i++) {
		if(resultVector[i] == subTreeRoot->data) {
			alreadyExists = true;
			break;
		}
	}

	if (!alreadyExists)  {
		resultVector.push_back(subTreeRoot->data);
		return;
	}

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
        bool contains = false;
        for (int i = 0; i < resultHolder.size(); i++) {
            if(resultHolder[i] == subTreeRoot->data)
                contains = true;
        }
		if(!contains)
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
    vector<int> testVector;
    testVector.push_back(14);
    testVector.push_back(15);
    testVector.push_back(12);
    assert(testVector == resultVector);
}


void testFindTrace ()
{
	cout << "Testing 'findTrace'" << endl;
	BTree<int> t;
	t.add(10,"").add(12,"L").add(14,"R").add(15,"LR").add(14, "LL").add(12, "RL");
	assert(t.findTrace(15)== "LR");
}

void testPrettyPrint()
{
	cout << "Testing pretty 'print'" << endl;
	BTree<int> t;
	t.add(10,"").add(12,"L").add(14,"R").add(15,"LR").add(14, "LL").add(12, "RL");
	t.prettyPrint();
}

void testAssignment()
{
	BTree<int> t;

	t.add(10,"").add(12,"L").add(14,"R").add(15,"LR");

	BTree<int> t1 = t;

	t1.map (plusOne);

	t1 = t;

	assert (t1.member(10) &&
		    t1.member (12) &&
		    t1.member (14) &&
		    t1.member (15));
    assert(t1.size() == 4);

}

void testMinEl ()
{
	BTree<int> t;

	t.insertBOT(59)
	 .insertBOT(23)
	 .insertBOT(68)
	 .insertBOT(190)
	 .insertBOT(41)
	 .insertBOT(67);

	 assert (t.minelement() == 23);
}

void testIndexOperator() {
	cout << "Testing operator [] " << endl;
	BTree<int> t;
	t.add(10,"").add(12,"L").add(14,"R").add(15,"LR").add(14, "LL").add(12, "RL").add(17, "RLL");
	assert(t[6] == 17);
}

void testSize()
{
	cout << "Testing 'size()' " << endl;
	BTree<int> t;
	t.add(10,"").add(12,"L").add(14,"R").add(15,"LR").add(14, "LL").add(12, "RL").add(17, "RLL");
	assert(t.size() == 7);
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
}

void testLevel() {
	cout << "Testing 'level' " << endl;
	BTree<int> test;
	test.add(10,"").add(12,"L").add(14,"R").add(15,"LR");
	vector<int> result = test.level(1);
    vector<int> compare;
    compare.push_back(12);
    compare.push_back(14);
    assert(compare == result);
}

void testHeight() {
	cout << "Testing 'height()' " << endl;
	BTree<int> test;
	test.add(10,"").add(12,"L").add(14,"R").add(15,"LR");
	assert(test.height() == 3);
}

void testDeletedBOT() {
    BTree<int> t;

	t.insertBOT(59)
	 .insertBOT(23)
	 .insertBOT(68)
	 .insertBOT(190)
	 .insertBOT(41)
	 .insertBOT(67);

	 BTree<int> result = t.deletedBOT(41);
	 assert(result.member(59) && result.member(23) && result.member(68) && result.member(190) && result.member(67));
	 assert(result.size() == 5);
     assert(result.member(41) == false);

     result = t.deletedBOT(59);
	 assert(result.member(41) && result.member(23) && result.member(68) && result.member(190) && result.member(67));
	 assert(result.size() == 5);
     assert(result.member(59) == false);

     result = t.deletedBOT(190);
	 assert(result.member(59) && result.member(23) && result.member(68) && result.member(41) && result.member(67));
     assert(result.size() == 5);
     assert(result.member(190) == false);

}

void testSameLevels() {
    BTree<int> test;
    test.add(5, "");
    test.add(5, "L");
    test.add(3, "R");
    test.add(5, "LL");
    test.add(3, "RL");
    test.add(3, "LR");

    test.prettyPrint();

    cout << test.hasSameLevels();

}

void testIsBOT() {
    BTree<int> t;

	t.insertBOT(59)
	 .insertBOT(23)
	 .insertBOT(68)
	 .insertBOT(190)
     .insertBOT(41)
	 .insertBOT(67);

	 assert (t.isBOT());

	 BTree<int> s;
	 s.add(5, "");
	 s.add(4,"R");

	 assert(!s.isBOT());

}

int main ()
{
    //assert(false);
    ///*
    testHeight();
	testLevel();
	testSize();
	testAssignment();
	testMember();
	testDeserializeScheme();
	testSerializeScheme();
	testIndexOperator();
	testMinEl();
	testPrettyPrint();
	testFindTrace();
	testListLeaves();
    testDeletedBOT();
    testSameLevels();
    testIsBOT();
	//*/
	return 0;
}
