// Name: Mareesh Kumar Issar
// Date of submission: Feb 26, 2019
// Course: 16:332:573, Data Structure and Algorithms
// Program name: Quick sort (naive approach- with cutoff)
// Source- Algorithms, 4th edition by Robert Sedgewick and Kevin Wayne and geeksforgeeks.org 

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <chrono>//for calculating execution time


using namespace std;
using namespace std::chrono;

int c = 0, cutoff = 7;

void quick_sort(vector<int> &a, int low, int high);
int partition(vector<int> &aux, int low, int high);


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

	//quicksort
	quick_sort(arr, 0, arr.size() - 1);

	//stop timer
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);


	cout << "Number of comparisons made is - " << c << endl;

	cout << "Function takes " << duration.count() << " microseconds" << endl;

	return 0;

}

int partition(vector<int> &a, int low, int high)
{
	int i, j, temp;

	i = low;
	j = high + 1;

	while (1)
	{
		while (a[++i] < a[low])
		{
			c++;
			if (i == high)
				break;
		}


		while (a[low] < a[--j])
		{
			c++;
			if (j == low)
				break;
		}


		if (i >= j)
		{
			c++;
			break;
		}


		temp = a[i];
		a[i] = a[j];
		a[j] = temp;

	}

	temp = a[low];
	a[low] = a[j];
	a[j] = temp;

	return j;

}




void quick_sort(vector<int> &a, int low, int high)
{
	int k, m, mid, temp;

	if (high <= (low + cutoff - 1))
	{
		//insertion sort
		int i, j, s;
		for (i = low + 1; i <= high; i++)
		{
			s = a[i];

			c++;//counting for initial comaparisons

			for (j = i - 1; j >= low && a[j] > s; c++, j--)//counting for comparisions made during exchanges
			{
				a[j + 1] = a[j];
			}

			a[j + 1] = s;

		}
		return;
	}


	mid = (low + high) / 2;

	//finding median of a[low], a[mid] and a[high]
	m = a[low] < a[mid] ?
		(a[mid] < a[high] ? mid : a[low] < a[high] ? high : low) :
		(a[high] < a[mid] ? mid : a[high] > a[low] ? low : high);

	temp = a[low];
	a[low] = a[m];
	a[m] = temp;


	k = partition(a, low, high);

	quick_sort(a, low, k - 1);
	quick_sort(a, k + 1, high);
}

