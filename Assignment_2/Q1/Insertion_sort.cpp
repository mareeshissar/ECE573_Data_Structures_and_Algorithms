// Name: Mareesh Kumar Issar
// Date of submission: Feb 26, 2019
// Course: 16:332:573, Data Structure and Algorithms
// Program name: Insertion sort
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
	int count=0,l,i,j,s;
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


		//insertion sort
		for (i = 1; i < arr.size(); i++)
		{
			s = arr[i];

			count++;//counting for initial comaparisons

			for (j = i - 1; j >= 0 && arr[j] > s; count++, j--)//counting for comparisions made during exchanges
			{
				arr[j + 1] = arr[j];
			}

			arr[j + 1] = s;

		}

		cout << "Number of comparisons made is - " << count << endl;

	return 0;
	
}

