// Name: Mareesh Kumar Issar
// Date of submission: April 30, 2019
// Course: 16:332:573, Data Structure and Algorithms
// Program name: Cycle detection
/* Source-

https://algs4.cs.princeton.edu/41graph/Cycle.java.html

*/


#include <iostream>
#include <fstream>
#include <iomanip>
#include <stack>
#include <string>
#include "EWGraph.h"


using namespace std;

class Cycle
{
	vector<bool> marked;
	vector<int> edgeTo;
	stack<int> cycle;

public:
	//function to check presence of a cycle
	bool hasCycle()
	{
		return !cycle.empty();
	}
	//function to get cycle
	stack<int> getCycle()
	{
		return cycle;
	}
	//function to detect cycle using dfs
	void dfs(EWGraph g, int a, int b)
	{
		marked[b] = true;

		for (WEdge edg : g.adj_list(b))
		{
			int e = edg.other(b);

			//if a cycle already found
			if (!cycle.empty())
				return;

			if (!marked[e])
			{
				edgeTo[e] = b;
				dfs(g,b, e);
			}

			//check for cycle
			else if (e != a)
			{
				for (int i = b; i != e; i = edgeTo[i])
				{
					cycle.push(i);

				}
				cycle.push(e);
				cycle.push(b);
			}

		}

	}
	//constructor
	Cycle(EWGraph g)
	{		
		marked.resize(g.V());
		edgeTo.resize(g.V());
		for (int i = 0; i < g.V(); i++)
		{
			if(!marked[i])
				dfs(g,-1, i);
		}
		
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

	Cycle c1(d1);
	
	if (c1.hasCycle())
	{
		cout << "The graph has cycle" << endl;
		path = c1.getCycle();
		while (!path.empty())
		{
			cout << path.top() <<"  ";
			path.pop();
		}
	}
	else
	{
		cout << "The graph is acyclic" << endl;
	}
	
	return 0;
}

