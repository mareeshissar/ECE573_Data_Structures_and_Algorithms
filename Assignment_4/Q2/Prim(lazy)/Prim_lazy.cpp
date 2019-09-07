// Name: Mareesh Kumar Issar
// Date of submission: April 30, 2019
// Course: 16:332:573, Data Structure and Algorithms
// Program name: Prim MST- Lazy approach
/* Source-

https://algs4.cs.princeton.edu/43mst/LazyPrimMST.java.html

https://www.geeksforgeeks.org/implement-min-heap-using-stl/
*/


#include <iostream>
#include <fstream>
#include <iomanip>
#include <queue>
#include <string>
#include <utility>//for pair
#include "EWGraph.h"
#include <chrono>//for calculating execution time


using namespace std;
using namespace std::chrono;
//creating a pair
typedef pair<double, vector<int>> pr;

class PrimMST
{
	double total_weight=0.0;
	queue<WEdge> mst;
	vector<bool> marked;

	priority_queue<pr, vector<pr>, greater<pr> > pq;

public:
	//function to get the total weight of the MST
	double weight()
	{
		return total_weight;
	}
	//function to get the edges of the MST
	queue<WEdge> edges()
	{
		return mst;
	}
	void scan(EWGraph g, int v)
	{
		vector<int> a;
		marked[v] = true;
		for (WEdge b : g.adj_list(v))
		{
			if (!marked[b.other(v)])
			{
				a.push_back(v);
				a.push_back(b.other(v));
				pq.push(make_pair(b.weight(),a));
				a.clear();//clearing the vector
			}
				

		}

	}
	//function to compute MST using prim algorithm
	void prim(EWGraph g, int s)
	{
		scan(g, s);
		while (!pq.empty())
		{
			vector<int> edg;
			edg = pq.top().second;
			int a = edg[0];
			int b = edg[1];
			WEdge e(a, b, pq.top().first);
			pq.pop();

			if (marked[a] && marked[b])
			{
				continue;
			}

			mst.push(e);
			total_weight = total_weight + e.weight();
			//scan the unmarked vertex
			if (!marked[a])
			{
				scan(g, a);
			}
			//scan the unmarked vertex
			if (!marked[b])
			{
				scan(g, b);
			}

		}
	}
	//constructor
	PrimMST(EWGraph g)
	{
		marked.resize(g.V());
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

	queue<WEdge> mst;

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
	cout << "MST using prim algorithm(lazy approach) is " << endl;
	while (!mst.empty())
	{
		cout << mst.front().either() << " -> " << mst.front().other(mst.front().either()) << " " << mst.front().weight() << endl;
		mst.pop();
	}
	cout << "Weight of the MST is " << p1.weight() << endl;
	
	return 0;
}

