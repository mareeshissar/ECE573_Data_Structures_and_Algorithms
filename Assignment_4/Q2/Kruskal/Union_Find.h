// Name: Mareesh Kumar Issar
// Date of submission: April 30, 2019
// Course: 16:332:573, Data Structure and Algorithms
// Program name: Kruskal MST-union find
/* Source-

https://algs4.cs.princeton.edu/43mst/KruskalMST.java.html

*/
#ifndef UNION_FIND_H
#define	UNION_FIND_H


#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>


using namespace std;


class UF
{
	vector<int> id;
	vector<int> sz;//to store the size of the tree(no. of objects in the tree)
public:
	//constructor- for initializing the vector-id with the total number of elements
	//constructor- for initializing the vector-sz with 1
	UF(int N)
	{
		for (int i = 0; i < N; i++)
		{
			id.push_back(i);
			sz.push_back(1);
		}
	}

	//function to find the root of element i
	int root(int i)
	{
		while (i != id[i])
		{
			i = id[i];
		}

		return i;
	}

	//function to add connection between two elements(by linking root of the smaller tree to the root of the larger tree)
	void Union(int p, int q)
	{
		int proot = root(p);
		int qroot = root(q);

		//check whether size of p's tree is smaller than size of q's tree
		if (sz[proot] < sz[qroot])
		{
			id[proot] = qroot;
			sz[qroot] += sz[proot];
		}

		else
		{
			id[qroot] = proot;
			sz[proot] += sz[qroot];
		}

	}

	//function to check whether two elements are connected or not
	bool connected(int p, int q)
	{
		return (root(p) == root(q));
	}

};


#endif