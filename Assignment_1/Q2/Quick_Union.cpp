// Name: Mareesh Kumar Issar
// Date of submission: Feb 19, 2019
// Course: 16:332:573, Data Structure and Algorithms
// Program name: Quick Union
// Source- Algorithms, 4th edition by Robert Sedgewick and Kevin Wayne and geeksforgeeks.org (for using chrono library)
// User Input- The maximum value for a point label(max no. of elements) for the input data set. It is 8192 for the data provided with this file

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <chrono>//for calculating execution time

using namespace std;
using namespace std::chrono;


class Quick_Union
{
	vector<int> id;
public:
	//constructor- for initializing the vector-id with the total number of elements
	Quick_Union(int N)
	{
		for (int i = 0; i < N; i++)
		{
			id.push_back(i);
		}
	}

	//function to find the root of element i
	int root(int i)
	{
		while (i != id[i])
			i = id[i];

		return i;
	}

	//function to add connection between two elements
	void Union(int p, int q)
	{
		int proot = root(p);
		int qroot = root(q);
		id[proot] = qroot;

	}

	//function to check whether two elements are connected or not
	bool connected(int p, int q)
	{
		return (root(p) == root(q));
	}

};

int main()
{
	int N, l, p, q;

	cout << "Enter the maximum value for a point label(max no. of elements) for the input data set " << endl;
	cin >> N;


	//start timer
	auto start = high_resolution_clock::now();


	//creating object of class Quick_Union
	Quick_Union qu(N);

	//reading data from file 
	ifstream file1("8pair.txt"); // change input file name here, file should be in the same folder in which this cpp file is present
	if (file1.is_open())
	{
		while (file1 >> l)
		{
			p = l;
			file1 >> l;
			q = l;

			if (qu.connected(p - 1, q - 1))//vector has range from 0 to N-1
				continue;

			qu.Union(p - 1, q - 1);//vector has range from 0 to N-1
			cout << "Doing union of " << p << " and " << q << endl;//this statement was commented while calculating execution time
		}

		file1.close();
	}

	else
	{
		cout << "Error in opening file" << endl;
	}


	//stop timer
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);


	cout << "Function takes " << duration.count() << " microseconds" << endl;



	return 0;
}

