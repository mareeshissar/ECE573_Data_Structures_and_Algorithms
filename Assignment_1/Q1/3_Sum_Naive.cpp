// Name: Mareesh Kumar Issar
// Date of submission: Feb 19, 2019
// Course: 16:332:573, Data Structure and Algorithms
// Program name: 3-Sum Naive implementation
// Source- Algorithms, 4th edition by Robert Sedgewick and Kevin Wayne and geeksforgeeks.org (for using chrono library)

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <chrono>//for calculating execution time

using namespace std;
using namespace std::chrono;

int main()
{
	vector<int> arr;
	int count = 0, l;

	//reading data from file into the vector-arr

	ifstream file1("8int.txt");	//change input file name here, file should be in the same folder in which this cpp file is present 
	if (file1.is_open())
	{
		while (file1 >> l)
		{
			arr.push_back(l);
		}

		file1.close();
	}

	else
	{
		cout << "Error in opening file" << endl;
	}

	//start timer
	auto start = high_resolution_clock::now();

	//3-sum naive implementation
	for (int i = 0; i < arr.size(); i++)
	{
		for (int j = i + 1; j < arr.size(); j++)
		{
			for (int k = j + 1; k < arr.size(); k++)
			{
				if (arr[i] + arr[j] + arr[k] == 0)
					count++;
			}
		}
	}

	//stop timer
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);

	cout << "Number of 3-sum pairs in the given data (using naive implementation) is - " << count << endl;

	cout << "Function takes " << duration.count() << " microseconds" << endl;

	return 0;
}

