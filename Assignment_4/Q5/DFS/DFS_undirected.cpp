// Name: Mareesh Kumar Issar
// Date of submission: April 30, 2019
// Course: 16:332:573, Data Structure and Algorithms
// Program name: DFS undirected weighted graph
/* Source-
https://algs4.cs.princeton.edu/41graph/DepthFirstPaths.java.html
*/


#include <iostream>
#include <fstream>
#include <iomanip>
#include <stack>
#include <string>
#include "EWGraph.h"


using namespace std;

class DFS_UD
{
	vector<bool> marked;
	vector<int> edgeTo;
	int source;

public:
	//function to check whether a path exists
	bool haspathTo(int a)
	{
		return marked[a];
	}
	//function to get path
	stack<int> pathTo(int b)
	{
		if (!haspathTo(b))
		{
			stack<int> def;
			return def;
		}


		stack<int> path;
		int i;
		for (i = b; i != source; i = edgeTo[i])
		{
			path.push(i);
		}
		path.push(i);
		return path;

	}
	//function to run DFS algorithm
	void dfs(EWGraph g, int s)
	{
		marked[s] = true;
		for (WEdge edg : g.adj_list(s))
		{
			int b = edg.other(s);

			if (!marked[b])
			{
				edgeTo[b] = s;
				dfs(g, b);
			}

		}

	}
	//constructor
	DFS_UD(EWGraph g, int s)
	{
		source = s;
		marked.resize(g.V());
		edgeTo.resize(g.V());
		dfs(g, s);
	}


};

int main()
{
	string file;
	stack<int> path;
	int s, d;

	cout << "Enter the file name" << endl;
	cin >> file;

	EWGraph d1(file);

	cout << "Number of vertices is " << d1.V() << endl;;
	cout << "Number of edges is " << d1.E() << endl;
	cout << "Enter the source vertex" << endl;
	cin >> s;
	DFS_UD b1(d1, s);
	cout << "Enter the destination vertex" << endl;
	cin >> d;
		
	path = b1.pathTo(d);
	if (path.empty())
	{
		cout << "no path exists" << endl;
	}
	else
	{
		while (!path.empty())
		{
			if (path.top() == s)
				cout << path.top();
			else
				cout << " -> " << path.top();
			path.pop();
		}
	}


	return 0;
}

