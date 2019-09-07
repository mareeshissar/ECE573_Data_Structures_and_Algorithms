// Name: Mareesh Kumar Issar
// Date of submission: Feb 26, 2019
// Course: 16:332:573, Data Structure and Algorithms
// Program name: Merge sort (recursive approach- with practical improvements)
// Source- Algorithms, 4th edition by Robert Sedgewick and Kevin Wayne and geeksforgeeks.org 


#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>


using namespace std;

int c=0,cutoff=7;

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

	//merge sort-recursive approach
	sort(arr, aux, 0, arr.size() - 1);

	cout << "Number of comparisons made is - " << c << endl;
	
	return 0;

}

void sort(vector<int> &a, vector<int> &aux, int low, int high)
{
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

	int mid = (high + low) / 2;

	sort(a, aux, low, mid);
	sort(a, aux, mid + 1, high);
	if (a[mid] < a[mid + 1])//condition to check whether the two halves are already sorted or not
	{
		c++;
		return;
	}
		
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
