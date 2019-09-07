// Name: Mareesh Kumar Issar
// Date of submission: April 30, 2019
// Course: 16:332:573, Data Structure and Algorithms
// Program name: Kruskal MST
/* Source-

https://algs4.cs.princeton.edu/43mst/KruskalMST.java.html

https://www.geeksforgeeks.org/implement-min-heap-using-stl/

*/


#include <iostream>
#include <fstream>
#include <iomanip>
#include <queue>
#include <stack>
#include <utility>//for pair
#include "EWGraph.h"
#include "Union_Find.h"
#include <chrono>//for calculating execution time


using namespace std;
using namespace std::chrono;
//creating a pair
typedef pair<double, vector<int>> pr;

class KruskalMST
{
	double total_weight = 0.0;
	queue<WEdge> mst;

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
	//constructor
	KruskalMST(EWGraph g)
	{
		vector<int> arr;
		//putting all the edges into a priority queue
		for (WEdge e : g.unique_edges())
		{
			arr.push_back(e.either());
			arr.push_back(e.other(e.either()));
			pq.push(make_pair(e.weight(), arr));
			arr.clear();
		}

		UF uf(g.V());
		while (!pq.empty() && mst.size() < g.V() - 1)
		{
			vector<int> edg;
			edg = pq.top().second;
			int a = edg[0];
			int b = edg[1];
			WEdge e(a, b, pq.top().first);
			pq.pop();

			//avoids creating cycles
			if (!uf.connected(a, b))
			{
				uf.Union(a, b);
				mst.push(e);
				total_weight = total_weight + e.weight();
			}
			
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

	KruskalMST p1(d1);
	
	//stop timer
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);

	cout << "Function takes " << duration.count() << " microseconds" << endl;

	cout << "MST using kruskal algorithm is " << endl;
	mst = p1.edges();
	while (!mst.empty())
	{
		cout << mst.front().either() << " -> " << mst.front().other(mst.front().either()) << " " << mst.front().weight() << endl;
		mst.pop();
	}
	cout << "Weight of the MST is " << p1.weight() << endl;
	
	return 0;
}

