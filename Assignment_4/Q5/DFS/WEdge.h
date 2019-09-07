#pragma once
// Name: Mareesh Kumar Issar
// Date of submission: April 30, 2019
// Course: 16:332:573, Data Structure and Algorithms
// Program name: DFS undirected weighted graph
/* Source-
https://algs4.cs.princeton.edu/41graph/DepthFirstPaths.java.html
*/

#ifndef WEDGE_H
#define	WEDGE_H


#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>


using namespace std;

class WEdge
{
	int a, b;
	double w;

public:
	//function to get a vertex
	int either()
	{
		return a;
	}
	//function to get other vertex
	int other(int vertex)
	{
		if (vertex == a) return b;
		else if (vertex == b) return a;
	}
	//function to get weights
	double weight()
	{
		return w;
	}
	//constructor
	WEdge(int a, int b, double w)
	{
		this->a = a;
		this->b = b;
		this->w = w;
	}
	/*
	WEdge()
	{
		this->a = -1;
		this->b = -1;
		this->w = 0.0;
	}*/
};

#endif