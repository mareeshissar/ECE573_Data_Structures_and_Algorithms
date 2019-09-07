// Name-Mareesh Kumar Issar
// Date of submission: April 30, 2019
// Course: 16:332:573, Data Structure and Algorithms
// Program name: BFS undirected weighted graph
/* Source-
https://algs4.cs.princeton.edu/41graph/BreadthFirstPaths.java.html

*/


#include <iostream>
#include <fstream>
#include <iomanip>
#include <queue>
#include <stack>
#include <string>
#include "EWGraph.h"


using namespace std;

class BFS_UD
{
	vector<bool> marked;
	vector<int> edgeTo;
	vector<int> distanceTo;



public:
	//function to return whether a path exists
	bool haspathTo(int a)
	{
		return marked[a];
	}
	//function to return shortest distance to a node
	int distTo(int a)
	{
		if (distanceTo[a] == INT_MAX)
			return -1;

		return distanceTo[a];
	}
	stack<int> pathTo(int b)
	{
		if (!haspathTo(b))
		{
			stack<int> def;
			return def;
		}


		stack<int> path;
		int i;
		for (i = b; distanceTo[i] != 0; i = edgeTo[i])
		{
			path.push(i);
		}
		path.push(i);
		return path;

	}
	//function to run bfs algorithm
	void bfs(EWGraph g, int s)
	{
		queue<int> q;
		marked[s] = true;
		distanceTo[s] = 0;
		q.push(s);
		while (!q.empty())
		{
			int a = q.front();
			q.pop();
			for (WEdge edg : g.adj_list(a))
			{
				int b = edg.other(a);

				if (!marked[b])
				{
					edgeTo[b] = a;
					distanceTo[b] = distanceTo[a] + 1;
					marked[b] = true;
					q.push(b);
				}

			}
		}

	}
	//constructor
	BFS_UD(EWGraph g, int s)
	{
		marked.resize(g.V());
		edgeTo.resize(g.V());
		distanceTo.resize(g.V());
		for (int i = 0; i < g.V(); i++)
		{
			distanceTo[i] = INT_MAX;
		}
		bfs(g, s);
	}


};

int main()
{
	string file;
	stack<int> sh_path;
	int s, d;

	cout << "Enter the file name" << endl;
	cin >> file;

	EWGraph d1(file);

	cout << "Number of vertices is " << d1.V() << endl;;
	cout << "Number of edges is " << d1.E() << endl;

	cout << "Enter the source vertex" << endl;
	cin >> s;
	BFS_UD b1(d1, s);
	cout << "Enter the destination vertex" << endl;
	cin >> d;

	cout << "Shortest hop count distance from " << s <<" to "<<d<< " is " << b1.distTo(d) << endl;
	sh_path = b1.pathTo(d);
	if (sh_path.empty())
	{
		cout << "no path exists" << endl;
	}
	else
	{
		while (!sh_path.empty())
		{
			if (sh_path.top() == s)
				cout << sh_path.top();
			else
				cout << " -> " << sh_path.top();
			sh_path.pop();
		}
	}


	return 0;
}

