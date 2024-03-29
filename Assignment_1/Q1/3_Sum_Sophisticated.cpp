// Name: Mareesh Kumar Issar
// Date of submission: Feb 19, 2019
// Course: 16:332:573, Data Structure and Algorithms
// Program name: 3-Sum Spohisticated implementation
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
	int count = 0;
	int smallest, small_index, temp, l;
	int low, high, mid;

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


	//selection sort- to arrange the elements in the vector-arr in ascending order
	for (int i = 0; i < arr.size(); i++)
	{
		smallest = arr[i];
		small_index = i;
		for (int j = i + 1; j < arr.size(); j++)
		{
			if (arr[j] < smallest)
			{
				smallest = arr[j];
				small_index = j;

			}
		}
		//swapping
		temp = arr[i];
		arr[i] = arr[small_index];
		arr[small_index] = temp;

	}

	//start timer
	auto start = high_resolution_clock::now();

	//3-sum sophisticated implementation
	for (int i = 0; i < arr.size() - 2; i++)
	{
		for (int j = i + 1; j < arr.size() - 1; j++)
		{
			//using binary search for finding the appropriate 3rd value(-(arr[i]+arr[j]))
			low = j + 1;
			high = arr.size() - 1;
			while (low <= high)
			{
				mid = (low + high) / 2;
				if (arr[mid] == -(arr[i] + arr[j]))
				{
					count++;
					break;
				}

				else if (arr[mid] > -(arr[i] + arr[j]))
					high = mid - 1;
				else
					low = mid + 1;

			}
		}
	}

	//stop timer
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);

	cout << "Number of 3-sum pairs in the given data (using sophisticated implementation) is - " << count << endl;

	cout << "Function takes " << duration.count() << " microseconds" << endl;

	return 0;
}

