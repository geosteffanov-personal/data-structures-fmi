#include <iostream>
#include <assert.h>
#include <stack>
#include <iomanip>

#include "binary-search-tree.cpp"

template <class T>
using mapFn = T (*)(const T&);

template <class T>
void simplePrint (BSTree<T> &t)
{
	cout << "{";
	for (T& x : t)
		cout << x << " ";
	cout << "}\n";
}

void testMember ()
{
	BSTree<int> t;

	t.add(10).add(12).add(14).add(15);

	assert (t.member(12) == true);
	assert (t.member(18) == false);
	assert (t.member(15) == true);
}


void testAssignment()
{
	BSTree<int> t;

	t.add(10).add(12).add(14).add(15);
	simplePrint(t);

	BSTree<int> t1;

	t1 = t;

	assert (t1.member(10) &&
		    t1.member (12) &&
		    t1.member (14) &&
		    t1.member (15));


}
void testMinEl ()
{
	BSTree<int> t;

	t.add(59)
	 .add(23)
	 .add(68)
	 .add(190)
	 .add(41)
	 .add(67);

	 assert (t.minelement() == 23);
}


void testIterator ()
{
	BSTree<int> t;

	t.add(59)
	 .add(23)
	 .add(68)
	 .add(190)
	 .add(41)
	 .add(67);


	 BSTree<int>::LERORIIterator it = t.begin();

	 assert (*it == 23);

	 ++it;
	 ++it;
	 assert (*it == 59);;

	 int count = 0;
	 for (it = t.begin(); it != t.end(); ++it)
	 {
	 	count++;
	 }


	 assert (count == 6);

}

template <class T>
void prettyPrint (typename BSTree<T>::HierarchicalIterator it,int depth=0)
{
	if (it.empty())
		return;

	prettyPrint<T> (it.goLeft(), depth + 1);

	cout << setw (depth*4) << " " << *it << endl;

	prettyPrint<T> (it.goRight(), depth + 1);
}

void testMakeTree ()
{
	BSTree<int> t;
	typename BSTree<int>::HierarchicalIterator it = t.rootIter();

	*it = 10;
	*it.goLeft() = 12;
	*it.goRight() = 14;

	prettyPrint<int> (it);

}


int main ()
{

	testMember ();
	testAssignment();
	testMinEl();
	testIterator();

	BSTree<int> t;

	t.add(56)
	 .add(23)
	 .add(68)
	 .add(190)
	 .add(41)
	 .add(60)
	 .add(65)
	 .add(59);


	cerr << "digraph G{" << endl;
	t.dottyPrint (cerr);
	cerr << "}\n";


	return 0;
}
