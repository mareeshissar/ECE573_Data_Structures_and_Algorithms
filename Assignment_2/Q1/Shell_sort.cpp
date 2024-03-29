// Name: Mareesh Kumar Issar
// Date of submission: Feb 26, 2019
// Course: 16:332:573, Data Structure and Algorithms
// Program name: Shell sort
// Source- Algorithms, 4th edition by Robert Sedgewick and Kevin Wayne and geeksforgeeks.org 

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>


using namespace std;


int main()
{   
	vector<int> arr;
	int count = 0, l, i, j, s,h;
	string file_name;

	cout << "Enter the file name: " << endl;
	cin >> file_name;

	//reading data from file into the vector-arr

	ifstream file1(file_name);	//file should be in the same folder in which this cpp file is present 
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


	h = 7;//largest value of h-sort

	while (h >= 1)
	{
		for (i = h; i < arr.size(); i++)
		{
			s = arr[i];

			count++;//counting for initial comaparisons
			for (j = i; j >= h && arr[j - h] > s; count++,j = j - h)//counting for comparisions made during exchanges
			{
				arr[j] = arr[j - h];
			}

			arr[j] = s;

		}

		h = h / 2;
	}

	cout << "Number of comparisons made is - " << count << endl;


	return 0;

}

