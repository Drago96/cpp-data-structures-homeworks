#include <iostream>
#include <string>
#include "BinOrdTree.cpp"


//task1
template <typename T>
bool binOrdTree<T>::contains(const node_bin<T>* p,T n) const
{
	if(p==NULL)
	{
		return false;
	}
	if(p->inf==n)
	{
		return true;
	}
	if(n<p->inf)
	{
		return contains(p->left,n);
	}
	else if(n>p->inf)
	{
		return contains(p->right,n);
	}
	return false;
}


template <typename T>
T binOrdTree<T>::smallestPredecessorHelper (const node_bin<T>* p,T x, T y) const
{
	if(p==NULL)
	{
		throw invalid_argument("tree is empty");
	}
	if((p->inf==x && contains(p,y)) || (p->inf==y && contains(p,x)))
	{
		return p->inf;
	}
	if((contains(p->left,x) && contains(p->right,y)) || (contains(p->right,x) && contains(p->left,y)))
	{
		return p->inf;
	}
	else if(contains(p->left,x) && contains(p->left,y))
	{
		return smallestPredecessorHelper(p->left,x,y);
	}
	else if(contains(p->right,x) && contains(p->right,y))
	{
		return smallestPredecessorHelper(p->right,x,y);
	}
	else
	{
		throw invalid_argument("one or more of the arguments are missing from the tree");
	}
	
}

template <typename T>
T binOrdTree<T>::smallestPredecessor (T x, T y) const
{
	T current=smallestPredecessorHelper(root,x,y);
	return current;
}

//task2
template <typename T>
void binOrdTree<T>::smallestInOrderHelper(const node_bin<T>* p,int k)  
{
  if (p) 
  {
    smallestInOrderHelper(p->left,k);
	counter++;
	if(k==counter)
	{
		cout << p->inf << " ";
		return;
	}
	smallestInOrderHelper(p->right,k);
  }
}

template <typename T>
void binOrdTree<T>::smallestInOrder(int k) 

{
	counter=0;
	smallestInOrderHelper(root,k);
	if(counter<k)
	{
		cout<<"element not found";
	}
	cout<<endl;
}


//task3
template <typename T>
node_bin<T>* binOrdTree<T>:: getRoot() const
{
	return this->root;
}

void sumNodes(node_bin<int>* root)
{
	if(root == NULL)
	{
		return;
	}
	sumNodes(root->left);
	sumNodes(root->right);
	if(root->left!=NULL)
	{
		root->inf+=root->left->inf;
	}
	if(root->right!=NULL)
	{
		root->inf+=root->right->inf;
	}
	

}

//task4
template <typename T>
void reverseBST(node_bin<T>* root)
{
	if(root==NULL)
	{
		return;
	}
	reverseBST(root->left);
	reverseBST(root->right);
	node_bin<T>* tempRight = root->right;
	root->right=root->left;
	root->left=tempRight;
}



int main()
{
	binOrdTree<int> testTree;
	cout<<"Create tree by typing in it's elements and selecting y/n about whether you want to add more elements"<<endl;
	testTree.create();
	cout<<"Initial tree: ";
	testTree.print();
	//task1
	cout<<"Find lowest common element of a and b: ";
	try
	{
		cout<<testTree.smallestPredecessor(4,14)<<endl;
	}
	catch(invalid_argument fail)
	{
		cerr<<fail.what()<<endl;
	}
	//task2
	cout<<"Find lowest element k: ";
	testTree.smallestInOrder(3);
	//task3
	cout<<"Sum nodes: ";
	sumNodes(testTree.getRoot());
	testTree.print();
	//task4
	cout<<"Reverse tree:";
	reverseBST(testTree.getRoot());
	testTree.print();
	return 0;
}