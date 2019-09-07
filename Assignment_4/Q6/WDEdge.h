#pragma once
// Name: Mareesh Kumar Issar
// Date of submission: April 30, 2019
// Course: 16:332:573, Data Structure and Algorithms
// Program name: Dijkstra algorithm- weighted directed edge processing
/* Source-

https://algs4.cs.princeton.edu/44sp/DijkstraSP.java.html

https://www.geeksforgeeks.org/implement-min-heap-using-stl/

https://www.geeksforgeeks.org/map-associative-containers-the-c-standard-template-library-stl/

*/

#ifndef WDEDGE_H
#define	WDEDGE_H


#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>


using namespace std;

class WDEdge
{
	int a,b;
	double w;

public:
	//function to get source vertex for edge
	int from()
	{
		return a;
	}
	//function to get destination vertex for edge
	int to()
	{
		return b;
	}
	//function to get weights
	double weight()
	{
		return w;
	}
	WDEdge(int a, int b, double w)
	{
		this->a = a;
		this->b = b;
		this->w = w;
	}
	WDEdge()
	{
		this->a = -1;
		this->b = -1;
		this->w = 0.0;
	}
};

#endif