// Name: Mareesh Kumar Issar
// Date of submission: Feb 19, 2019
// Course: 16:332:573, Data Structure and Algorithms
// Program name: Fastest 3-Sum
// Source-https://www.byte-by-byte.com/threesum/ and geeksforgeeks.org (for using chrono library)

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
	int smallest, small_index, temp, l, begin, end;

	//reading data from file into the vector-arr

	ifstream file1("8int.txt");//change input file name here, file should be in the same folder in which this cpp file is present 
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

	//selection sort- to arrange the array in ascending order
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

/*
	//linear algorithm for counting no. of pairs that sum to 0(sorted array)
	count = 0;
	//two variables pointing at the ends of the array
	begin = 0;
	end = arr.size() - 1;

	while(begin<end)
	{
		if ((arr[begin] + arr[end]) == 0)
		{
			count++;
			//checking for duplicates
			do
			{
				temp = begin;
				begin++;
			} while (arr[temp]==arr[begin]);

		}
		else if ((arr[begin] + arr[end]) < 0)
			begin++;
		else if ((arr[begin] + arr[end]) > 0)
			end--;
	}

	cout << "Number of 2-sum pairs in the given data (using linear implementation) is - " << count << endl;
*/



	//start timer
	auto start = high_resolution_clock::now();

	for (int i = 0; i < arr.size()-3; i++)
	{
		//for removing duplicates from counting
		if (i == 0 || arr[i] > arr[i - 1])
		{
			//modified linear algorithm for counting no. of pairs that sum to 0(sorted array)
			
			//variables pointing to the ends of the sub-array
			begin = i + 1;
			end = arr.size() - 1;

			while (begin < end)
			{
				if ((arr[i] + arr[begin] + arr[end]) == 0)
				{
					count++;

					//for removing duplicates from counting
					do
					{
						temp = begin;
						begin++;
					} while (arr[temp] == arr[begin]);

				}
				else if ((arr[i] + arr[begin] + arr[end]) < 0)
					begin++;
				else if ((arr[i] + arr[begin] + arr[end]) > 0)
					end--;
			}

		}
		
	}


	//stop timer
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);

	cout << "Number of 3-sum pairs in the given data (using n^2 implementation) is - " << count << endl;

	cout << "Function takes " << duration.count() << " microseconds" << endl;



	return 0;
}


