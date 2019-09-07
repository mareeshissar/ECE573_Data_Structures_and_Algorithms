// Name: Mareesh Kumar Issar
// Date of submission: April 30, 2019
// Course: 16:332:573, Data Structure and Algorithms
// Program name: Dijkstra algorithm
/* Source-

https://algs4.cs.princeton.edu/44sp/DijkstraSP.java.html

https://www.geeksforgeeks.org/implement-min-heap-using-stl/

https://www.geeksforgeeks.org/map-associative-containers-the-c-standard-template-library-stl/

*/


#include <iostream>
#include <fstream>
#include <iomanip>
#include <queue>
#include <stack>
#include <map>
#include <utility>//for pair
#include "EWDigraph.h"


using namespace std;


class Dijkstra
{
	vector<WDEdge> edgeTo;
	vector<double> distanceTo;
	
	map<double, int> pq;

public:
	//function to check whether a path exists
	bool haspathTo(int a)
	{
		return distanceTo[a]<DBL_MAX;
	}
	//function to return distance
	double distTo(int a)
	{
		if (distanceTo[a] == DBL_MAX)
			return -1;

		return distanceTo[a];
	}
	//function to return the shortest path
	stack<WDEdge> pathTo(int b)
	{
		if (!haspathTo(b))
		{
			stack<WDEdge> def;
			return def;
		}


		stack<WDEdge> path;
		for (WDEdge e = edgeTo[b]; e.from()!=-1; e = edgeTo[e.from()])
		{
			path.push(e);
		}
	
		return path;

	}
	//constructor implements dijkstra's algorithm
	Dijkstra(EWDigraph g, int s)
	{
		edgeTo.resize(g.V());
		distanceTo.resize(g.V());
		for (int i = 0; i < g.V(); i++)
		{
			distanceTo[i] = DBL_MAX;
		}
		
		distanceTo[s] = 0.0;
		pq.insert(make_pair(distanceTo[s],s));
		
		while (!pq.empty())
		{
			double first = pq.begin()->first;
			int second = pq.begin()->second;
			pq.erase(first);
			
			for (WDEdge edg : g.adj_list(second))
			{
				int c = edg.from();
				int d = edg.to();

			
				if (distanceTo[d] > (distanceTo[c] + edg.weight()) )
				{
					
					distanceTo[d] = distanceTo[c] + edg.weight();
					edgeTo[d] = edg;
					pq.erase(distanceTo[d]);
					pq.insert(make_pair(distanceTo[d],d));
				}

			}
		}

	}


};

int main()
{
	string file;
	stack<WDEdge> sh_path;
	int s, d;

	cout << "Enter the file name" << endl;
	cin >> file;

	EWDigraph d1(file);
	cout << "Number of vertices is " << d1.V() << endl;;
	cout << "Number of edges is " << d1.E() << endl;

	cout << "Enter the source vertex" << endl;
	cin >> s;
	Dijkstra b1(d1, s);
	for (int i = 0; i < d1.V(); i++)
	{
		sh_path = b1.pathTo(i);
		if (sh_path.empty())
		{
			cout << "no path exists" << endl;
		}
		else
		{
			while (!sh_path.empty())
			{
				cout << sh_path.top().from() << "->" << sh_path.top().to() << " w " << sh_path.top().weight()<<endl;
				sh_path.pop();
			}
		}
		cout << "----------" << endl;
	}

	return 0;
}

