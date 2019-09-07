#pragma once
// Name: Mareesh Kumar Issar
// Date of submission: April 30, 2019
// Course: 16:332:573, Data Structure and Algorithms
// Program name: DFS undirected weighted graph
/* Source-
https://algs4.cs.princeton.edu/41graph/DepthFirstPaths.java.html
*/

#ifndef EWGRAPH_H
#define	EWGRAPH_H


#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

#include "WEdge.h"

using namespace std;


class EWGraph
{
	int v, e;
	vector<vector<WEdge>> adj;

public:
	//function to get number of vertices
	int V()
	{
		return v;
	}
	//function to get number of edges
	int E()
	{
		return e;
	}
	//function to add a edge
	void addEdge(WEdge e)
	{
		int a = e.either();
		int b = e.other(a);
		adj[a].push_back(e);
		adj[b].push_back(e);
	}
	//function to get adjacent vertices
	vector<WEdge> adj_list(int a)
	{
		return adj[a];
	}
	//constructor
	EWGraph(string file_name)
	{
		//reading data from file 
		ifstream file1(file_name);
		int in, a, b;
		double d, w;

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
				addEdge(WEdge(a, b, w));
			}


		}

		else
		{
			cout << "Error in opening file" << endl;
		}
		/*for debugging*/
		/*
		int i, j;
		cout << "data" << endl;
		for (i = 0; i < v; i++)
		{
			for (j = 0; j < adj[i].size(); j++)
			{
				cout << "from" << adj[i][j].either() << "   " << "to" << adj[i][j].other(adj[i][j].either()) << "   " << "weight" << adj[i][j].weight();
			}
			cout << endl;
		}
		*/
	}

};

#endif