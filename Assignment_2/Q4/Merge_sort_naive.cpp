// Name: Mareesh Kumar Issar
// Date of submission: Feb 26, 2019
// Course: 16:332:573, Data Structure and Algorithms
// Program name: Merge sort (recursive naive approach)
// Source- Algorithms, 4th edition by Robert Sedgewick and Kevin Wayne and geeksforgeeks.org 


#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <chrono>//for calculating execution time


using namespace std;
using namespace std::chrono;

int c = 0;

void sort(vector<int> &a, vector<int> &aux, int low, int high);
void merge(vector<int> &a, vector<int> &aux, int low, int mid, int high);


int main()
{
	vector<int> arr;

	int l;
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

	vector<int> aux(arr.size());

	//start timer
	auto start = high_resolution_clock::now();
	//merge sort-recursive approach
	sort(arr, aux, 0, arr.size() - 1);
	//stop timer
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);


	cout << "Number of comparisons made is - " << c << endl;

	cout << "Function takes " << duration.count() << " microseconds" << endl;

	return 0;

}

void sort(vector<int> &a, vector<int> &aux, int low, int high)
{
	if (high <=low)
	{
		return;
	}

	int mid = (high + low) / 2;

	sort(a, aux, low, mid);
	sort(a, aux, mid + 1, high);
	merge(a, aux, low, mid, high);
}

void merge(vector<int> &a, vector<int> &aux, int low, int mid, int high)
{
	//copying sorted subarrays into auxillary array
	for (int k = low; k <= high; k++)
	{
		aux[k] = a[k];

	}

	int i = low;
	int j = mid + 1;

	for (int k = low; k <= high; k++)
	{
		if (i > mid)
			a[k] = aux[j++];

		else if (j > high)
			a[k] = aux[i++];

		else if (aux[j] < aux[i])
		{
			a[k] = aux[j++];
			c++;
		}
			

		else
		{
			a[k] = aux[i++];
			c++;
		}
			
		
	}
}
