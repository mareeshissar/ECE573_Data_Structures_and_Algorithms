// Name: Mareesh Kumar Issar
// Date of submission: Feb 26, 2019
// Course: 16:332:573, Data Structure and Algorithms
// Program name: Merge sort (bottom-up approach)
// Source- Algorithms, 4th edition by Robert Sedgewick and Kevin Wayne and geeksforgeeks.org 


#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>


using namespace std;

int c = 0;

void sort_bu(vector<int> &a, vector<int> &aux);
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


	//merge sort bottom-up approach
	sort_bu(arr,aux);


	cout << "Number of comparisons made is - " << c << endl;
	
	return 0;

}

void sort_bu(vector<int> &a, vector<int> &aux)
{
	int step, mid, low, high;
	for (step = 1; step < a.size(); step = step * 2)//runs for all the possible sizes of subarrays
	{
	
		for (low = 0; low < (a.size() - step); low += step + step)
		{
			mid = low + step - 1;

			if (low + step + step - 1 < (a.size() - 1))
				high = low + step + step - 1;
			
			else
				high = a.size() - 1;

			merge(a, aux, low, mid, high);
		}
	}


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
