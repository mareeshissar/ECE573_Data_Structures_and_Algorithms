// Name: Mareesh Kumar Issar
// Date of submission: April 30, 2019
// Course: 16:332:573, Data Structure and Algorithms
// Program name: Prim MST- Eager approach
/* Source-

https://algs4.cs.princeton.edu/43mst/PrimMST.java.html

https://www.geeksforgeeks.org/implement-min-heap-using-stl/

*/


#include <iostream>
#include <fstream>
#include <iomanip>
#include <queue>
#include <map>
#include <string>
#include "EWGraph.h"
#include <chrono>//for calculating execution time


using namespace std;
using namespace std::chrono;

class PrimMST
{
	double total_weight = 0.0;

	vector<WEdge> edgeTo;
	vector<double> distanceTo;
	vector<bool> marked;

	map<double, int> pq;
	

public:
	//function to get the total weight of the MST
	double weight()
	{
		for (WEdge e : edges())
			total_weight = total_weight + e.weight();
		return total_weight;
	}
	//function to get the edges of the MST
	vector<WEdge> edges()
	{
		vector<WEdge> mst;
		for (int i = 0; i < edgeTo.size(); i++)
		{
			WEdge e = edgeTo[i];
			if (e.weight() != NULL)
				mst.push_back(e);
		}
		return mst;
	}
	void scan(EWGraph g, int v)
	{
		int c = 0;
		marked[v] = true;
		for (WEdge b : g.adj_list(v))
		{
			int w = b.other(v);
			
			if (marked[w])
				continue;

			if (b.weight() < distanceTo[w])
			{
				distanceTo[w] = b.weight();
				edgeTo[w] = b;
				
				//removing the entry from map if vertex is already present
				map<double, int>::iterator it;
				map<double, int>::iterator it_delete;
				//pq.erase(5);
				for (it = pq.begin(); it != pq.end(); it++)
				{
					if (it->second == w)
					{
						it_delete = it;
						c = 1;//setting the counter
					}

				}
				if (c == 1)
				{
					pq.erase(it_delete);
					c = 0;//resetting the counter
				}
					
				//inserting updated entry
				pq.insert(make_pair(distanceTo[w],w));
			}

		}

	}
	

	//function to compute MST using Prim algorithm
	void prim(EWGraph g, int s)
	{
		distanceTo[s] = 0.0;
		pq.insert(make_pair(distanceTo[s], s));
		while (!pq.empty())
		{
			double first = pq.begin()->first;
			int second = pq.begin()->second;
			pq.erase(first);
			scan(g, second);
		}
	}

	
	//constructor
	PrimMST(EWGraph g)
	{
		edgeTo.resize(g.V());
		distanceTo.resize(g.V());
		marked.resize(g.V());
		for (int i = 0; i < g.V(); i++)
		{
			distanceTo[i] = DBL_MAX;
		}

		for (int i = 0; i < g.V(); i++)
		{
			if (!marked[i])
				prim(g, i);
		}

	}


};

int main()
{
	string file;
	int s, d;

	vector<WEdge> mst;

	cout << "Enter the file name" << endl;
	cin >> file;

	EWGraph d1(file);
	cout << "Number of vertices is " << d1.V() << endl;;
	cout << "Number of edges is " << d1.E() << endl;

	//start timer
	auto start = high_resolution_clock::now();

	PrimMST p1(d1);

	//stop timer
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);


	cout << "Function takes " << duration.count() << " microseconds" << endl;

	mst = p1.edges();
	cout << "MST using prim algorithm(eager approach) is " << endl;
	for(int i=0;i<mst.size();i++)
	{
		cout << mst[i].either() << " -> " << mst[i].other(mst[i].either()) << " " << mst[i].weight() << endl;
	}

	cout << "weight of the MST is " << p1.weight() << endl;

	return 0;
}

