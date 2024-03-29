// Name: Mareesh Kumar Issar
// Date of submission: Feb 19, 2019
// Course: 16:332:573, Data Structure and Algorithms
// Program name: Farthest Pair
// User Input- Number of elements in the array and the elements


#include <iostream>

using namespace std;

int main()
{
	int N;
	double smallest, largest, l;

	cout << "Enter the number of elements in the array " << endl;
	cin >> N;

	double *a = new double[N];

	//initializing the array
	for (int i = 0; i < N; i++)
	{
		cout << endl << "Enter element " << i + 1 << endl;
		cin >> a[i];
	}

	//setting the smallest and the largest value in the array- default
	smallest = a[0];
	largest = a[0];

	//finding the smallest and the largest number in the array
	for (int i = 1; i < N; i++)
	{
		if (a[i] <= smallest)
			smallest = a[i];
		if (a[i] >= largest)
			largest = a[i];
	}

	cout << endl << "The farthest pair is:- " << smallest <<" and " << largest << endl;
	
	delete[] a;
	return 0;
}

