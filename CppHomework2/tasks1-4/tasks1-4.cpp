#include <iostream>
#include "graph.cpp"
#include "llist.cpp"

//helper functions
template <typename T>
void addRibs(graph<T>& g, T from, T to)
{
	g.addRib(from, to);
	g.addRib(to, from);
}

template <typename T>
bool contains(LList<T> & list, T x)
{
	list.IterStart();
	elem_link1<T>* p;
	while ((p = list.Iter()))
	{
		if (p->inf == x)
		{
			return true;
		}
	}
	return false;
}

template <typename T>
void deleteElement(LList<T>& list, T x)
{
	list.IterStart();
	elem_link1<T>* p;
	while ((p = list.Iter()))
	{
		if (p->inf == x)
		{
			list.DeleteElem(p, x);
			return;
		}
	}
}

//task 1
template <typename T>
void isConnectedHelper(graph<T>& g, LList<T>& vertexes, T currVertex)
{
	deleteElement(vertexes, currVertex);

	elem_link1<T>* neighbours = g.point(currVertex);
	while (neighbours->link)
	{
		neighbours = neighbours->link;
		T next = neighbours->inf;
		if (contains(vertexes, next))
		{
			isConnectedHelper(g, vertexes, next);
		}
	}

}

template <typename T>
bool isConnected(graph<T>& g)
{
	if (g.vertexes().empty())
	{
		return true;
	}
	LList<T> vertexes = g.vertexes();
	vertexes.IterStart();
	elem_link1<T>* startVertex = vertexes.Iter();
	T startVertexValue = startVertex->inf;
	isConnectedHelper(g, vertexes, startVertexValue);
	return vertexes.empty();
}

//task 2
template <typename T>
void printComponentsHelper(graph<T>& g, LList<T>& vertexes, int k)
{
	if (!vertexes.empty())
	{
		cout << "Component " << k << ": ";
		vertexes.IterStart();
		elem_link1<T>* startVertex = vertexes.Iter();
		T startVertexValue = startVertex->inf;
		printComponent(g, vertexes, startVertexValue, k);
		cout << endl;
		printComponentsHelper(g, vertexes, k + 1);
	}
}

template <typename T>
void printComponent(graph<T>& g, LList<T>& vertexes, T currVertex, int k)
{
	cout << currVertex << " ";
	deleteElement(vertexes, currVertex);

	elem_link1<T>* neighbours = g.point(currVertex);
	while (neighbours->link)
	{
		neighbours = neighbours->link;
		T next = neighbours->inf;
		if (contains(vertexes, next))
		{
			printComponent(g, vertexes, next,k);
		}
	}
}

template <typename T>
void printComponents(graph<T>& g)
{
	if (g.vertexes().empty())
	{
		cout << "Graph is empty" << endl;
		return;
	}
	LList<T> vertexes = g.vertexes();
	int k = 1;
	printComponentsHelper(g, vertexes,k);
}

//task3
template <typename T>
void deleteRib(graph<T>& g, T pointFrom, T pointTo)
{
	elem_link1<T>* ribStart = g.point(pointFrom);
	elem_link1<T>* currRib;
	while (ribStart->link)
	{
		currRib = ribStart->link;
		if (currRib->inf == pointTo)
		{
			ribStart->link = currRib->link;
			delete currRib;
			return;
		}

		ribStart = ribStart->link;

	}
}

template <typename T>
void coveringTree(graph<T>& g)
{
	if (g.vertexes().empty())
	{
		cout<<"Graph is empty";
		return;
	}
	LList<T> vertexes = g.vertexes();
	vertexes.IterStart();
	elem_link1<T>* currVertex = vertexes.Iter();
	cout << "Covering Tree: ";
	while (currVertex)
	{
		T currPoint = currVertex->inf;
		elem_link1<T>* ribStart = g.point(currPoint);
		if (ribStart->link)
		{
			T pointTo = ribStart->link->inf;
			cout << currPoint << "->" << pointTo << " ";
			deleteRib(g, currPoint, pointTo);
			deleteRib(g, pointTo, currPoint);
		}
		currVertex = vertexes.Iter();
	}
	cout << endl;
}

//task 4
template <typename T>
bool hasCycle(graph<T>& g, T currVertex, LList<T>& visited)
{
	if (contains(visited, currVertex))
	{
		return true;
	}
	visited.ToEnd(currVertex);
	elem_link1<T>* neighbours = g.point(currVertex);
	while (neighbours->link)
	{
		neighbours = neighbours->link;
		T next = neighbours->inf;
		if (hasCycle(g, next, visited))
		{
			return true;
		}
	}
	return false;

}

template<typename T>
bool hasCycles(graph<T>& g)
{
	LList<T> vertexes = g.vertexes();
	if (vertexes.empty())
	{
		return true;
	}
	vertexes.IterStart();
	elem_link1<T>* currVertex = vertexes.Iter();
	while (currVertex)
	{
		LList<T> visited;
		T vertexValue = currVertex->inf;
		if (hasCycle(g, vertexValue,visited))
		{
			return true;
		}
		currVertex = vertexes.Iter();
	}
	return false;
}

int main()
{
	//graph used for tasks 1 - 3
	graph<int> g;
	g.addTop(1);
	g.addTop(2);
	g.addTop(3);
	addRibs(g, 1, 2);
	addRibs(g, 1, 3);
	//task 1
	cout << isConnected(g)<<endl;
	//task 2
	printComponents(g);
	//task 3
	coveringTree(g);

	//graph used for task 4
	graph<int> g1;
	g1.addTop(1);
	g1.addTop(2);
	g1.addTop(3);
	g1.addRib(1, 2);
	g1.addRib(2, 3);
	g1.addRib(3, 1);
	cout << hasCycles(g1) << endl;
	return 0;
}
