// Name: Mareesh Kumar Issar
// Date of submission: Feb 26, 2019
// Course: 16:332:573, Data Structure and Algorithms
// Program name: Kendall tau distance using merge sort
// Source- Algorithms, 4th edition by Robert Sedgewick and Kevin Wayne and geeksforgeeks.org 
// Input- First enter the data0.* file then enter data1.* file. NOTE: Here * should be the same number


#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <chrono>//for calculating execution time


using namespace std;
using namespace std::chrono;

int c = 0;

int sort(vector<int> &a, vector<int> &aux, int low, int high);
int merge(vector<int> &a, vector<int> &aux, int low, int mid, int high);


int main()
{
	vector<int> arr;
	vector<int> arr1;

	int l, inv;
	string file_name;

	cout << "Enter the file 1 name: " << endl;
	cin >> file_name;

	//reading data from file 1 into the vector-arr

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

	cout << "Enter the file 2 name: " << endl;
	cin >> file_name;

	//reading data from file 2 into the vector-arr1

	ifstream file2(file_name);	//file should be in the same folder in which this cpp file is present 
	if (file2.is_open())
	{
		while (file2 >> l)
		{
			arr1.push_back(l);
		}

		file2.close();
	}

	else
	{
		cout << "Error in opening file" << endl;
	}


	vector<int> ainv(arr.size());
	for (int f = 0; f < arr.size(); f++)
	{
		ainv[arr[f] - 1] = f;//arr[f]-1 because the numbers in the vector starts from 1
	}

	//number of inversions in bnew is the kendall tau distance
	vector<int> bnew(arr.size());
	for (int f = 0; f < arr.size(); f++)
	{
		bnew[f] = ainv[arr1[f] - 1];
	}



	vector<int> aux(arr.size());

	//start timer
	auto start = high_resolution_clock::now();
	//merge sort-recursive approach
	inv = sort(bnew, aux, 0, arr.size() - 1);
	//stop timer
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);


	cout << "Number of comparisons made (in worst case) is - " << c << endl;
	cout << "Number of inversion pairs is - " << inv << endl;


	cout << "Function takes " << duration.count() << " microseconds" << endl;

	return 0;

}

int sort(vector<int> &a, vector<int> &aux, int low, int high)
{
	int inv_count1 = 0;

	if (high <= low)
	{
		return inv_count1;
	}

	int mid = (high + low) / 2;

	inv_count1 = sort(a, aux, low, mid);
	inv_count1 += sort(a, aux, mid + 1, high);
	inv_count1 += merge(a, aux, low, mid, high);
}

int merge(vector<int> &a, vector<int> &aux, int low, int mid, int high)
{
	int inv_count = 0;
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
			inv_count = inv_count + ((mid + 1) - i);

		}


		else
			a[k] = aux[i++];

		c++;
	}

	return inv_count;
}
