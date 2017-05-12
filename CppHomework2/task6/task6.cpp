#include<iostream>
#include<vector>
#include<map>

using namespace std;

//task 6
class wgraph
{
public:
	void addTop();
	void addRib(int from,int to,int weight);

	map<int, int> getNeighbours(int point);

	int getWeight(int from, int to);
private:
	vector<map<int, int>> g;
};

void wgraph::addTop()
{
	map<int, int> newNode;
	g.push_back(newNode);
}

void wgraph::addRib(int from, int to,int weight)
{
	g[from-1][to] = weight;
}

map<int, int> wgraph::getNeighbours(int point)
{
	return g[point - 1];
}

int wgraph::getWeight(int from, int to)
{
	return g[from - 1][to];
}

bool contains(vector<int> v, int num)
{
	for (int i = 0; i < v.size(); i++)
	{
		if (v[i] == num)
		{
			return true;
		}
	}
	return false;
}

void findPathsFromTo(int from, int to, wgraph& g, vector<int> visited, vector<vector<int>>& paths)
{
	visited.push_back(from);
	if (from == to)
	{
		paths.push_back(visited);
	}
	map<int, int> neighbours = g.getNeighbours(from);
	map<int, int>::iterator it;
	for (it = neighbours.begin(); it != neighbours.end(); it++)
	{
		if (!contains(visited, it->first))
		{
			findPathsFromTo(it->first, to, g, visited, paths);
		}
	}

}

vector<vector<int>> findAllPathsFromTo(int from, int to, wgraph& g)
{
	vector<int> visited;
	vector <vector<int>> paths;
	findPathsFromTo(from, to, g, visited, paths);
	return paths;
}

int findPathWeight(vector<int>& path, wgraph& g)
{
	int weight = 0;
	for (int i = 0; i < path.size() - 1; i++)
	{
		weight += g.getWeight(path[i], path[i + 1]);
	}
	return weight;
}

void printShortestPath(vector<vector<int>>& paths, wgraph& g)
{
	vector<int> shortestPath = paths[0];
	int shortestLength = findPathWeight(paths[0], g);
	for (int i = 1; i < paths.size(); i++)
	{
		if (paths[i].size() < shortestPath.size() || (paths[i].size() == shortestPath.size() && findPathWeight(paths[i],g) < shortestLength))
		{
			shortestPath = paths[i];
			shortestLength = findPathWeight(paths[i], g);
		}
	}
	cout << endl;
	cout << shortestLength << endl;
	for (int i = 0; i < shortestPath.size(); i++)
	{
		cout << shortestPath[i] << " ";
	}
	cout << endl;
}

int main()
{
	wgraph g;
	int nodesNum, ribsNum;
	scanf_s("%i %i", &nodesNum, &ribsNum);
	for (int i = 0; i < nodesNum; i++)
	{
		g.addTop();
	}
	int nodeFrom, nodeTo, weight;
	for (int i = 0; i < ribsNum; i++)
	{
		scanf_s("%i %i %i", &nodeFrom, &nodeTo, &weight);
		g.addRib(nodeFrom, nodeTo, weight);
		g.addRib(nodeTo, nodeFrom, weight);
	}
	vector<vector<int>> paths = findAllPathsFromTo(1, nodesNum, g);
	printShortestPath(paths, g);

	return 0;
	
}