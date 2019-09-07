#pragma once
// Name: Mareesh Kumar Issar
// Date of submission: April 30, 2019
// Course: 16:332:573, Data Structure and Algorithms
// Program name: Dijkstra algorithm- weighted directed graph processing
/* Source-

https://algs4.cs.princeton.edu/44sp/DijkstraSP.java.html

https://www.geeksforgeeks.org/implement-min-heap-using-stl/

https://www.geeksforgeeks.org/map-associative-containers-the-c-standard-template-library-stl/

*/

#ifndef EWDIGRAPH_H
#define	EWDIGRAPH_H


#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

#include "WDEdge.h"

using namespace std;


class EWDigraph
{
	int v, e;

	vector<vector<WDEdge>> adj;

public:
	//function to get the number of vertices
	int V()
	{
		return v;
	}
	//function to get the number of edges
	int E()
	{
		return e;
	}
	//function to add edge
	void addEdge(WDEdge e)
	{
		int a = e.from();
		adj[a].push_back(e);
	}
	//function to get adjacent vertices
	vector<WDEdge> adj_list(int a)
	{
		return adj[a];
	}
	//constructor
	EWDigraph(string file_name)
	{
		//reading data from file 
		ifstream file1(file_name);
		int in, a, b;
		double d,w;

		if (file1.is_open())
		{
			file1 >> in;
			this->v = in;

			adj.resize(v);
			file1 >> in;
			this->e = in;

			for (int i = 0; i < e; i++)
			{
				file1 >> in;
				a = in;

				file1 >> in;
				b = in;

				file1 >> d;
				w = d;
				addEdge(WDEdge(a, b, w));
			}


		}

		else
		{
			cout << "Error in opening file" << endl;
		}
		int i, j;
		cout << "data" << endl;
		for (i = 0; i < v; i++)
		{
			for (j = 0; j < adj[i].size(); j++)
			{
				cout << "from"<< adj[i][j].from() << "   " << "to"<<adj[i][j].to()<<"   "<<"weight"<<adj[i][j].weight();
			}
			cout << endl;
		}
	}

};

#endif