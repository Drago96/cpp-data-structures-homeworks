#include <iostream>
#include <map>
#include <vector>
#include "binOrdTree.cpp"

using namespace std;

//task 5
template<typename T>
void addToColumns(binOrdTree<T>& t, map<int, vector<T>>& columns, int k)
{
	if (t.empty())
	{
		return;
	}
	addToColumns(t.leftTree(), columns, k - 1);
	columns[k].push_back(t.rootTree());
	addToColumns(t.rightTree(), columns, k + 1);
}

template<typename T>
void printColumn(vector<T>& v)
{
	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;
}


template <typename T>
void printByColumns(binOrdTree<T>& t)
{
	map<int, vector<T>> columns;
	int k = 0;
	addToColumns(t, columns, k);
	for (std::map<int, vector<T>>::iterator it = columns.begin(); it != columns.end(); ++it)
	{
		printColumn(it->second);
	}
}

int main()
{
	binOrdTree<int> tree;
	tree.create();
	printByColumns(tree);
}