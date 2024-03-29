// Name: Mareesh Kumar Issar
// Date of submission: April 02, 2019
// Course: 16:332:573, Data Structure and Algorithms
// Program name: Left Leaning Red Black Tree (calculating path length)
/* Source-

https://algs4.cs.princeton.edu/33balanced/RedBlackBST.java.html

https://algs4.cs.princeton.edu/11model/Knuth.java.html

https://gist.github.com/mycodeschool/44e1a9183ab0e931f729

*/

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <math.h>
using namespace std;

struct Node
{
	int key;
	int value;
	Node *left, *right;
	bool color;
	int size;
	Node(int key, int value, bool color)
	{
		this->key = key;
		this->value = value;
		this->left = NULL;
		this->right = NULL;
		this->size = 1;
		this->color = color;
	}

};

class LLRBT
{
	Node *root = NULL;//initially tree is empty

	const bool RED = true;
	const bool BLACK = false;

	int rcount = 0;//keeps count of red links/nodes
	int tcount = 0;//keeps count of total links/nodes

	//function to insert key-value pair
	Node* put(Node* x, int key, int value)
	{
		if (x == NULL)
		{
			Node *newnode = new Node(key, value, RED);//new node creation
			return newnode;
		}


		if (key < x->key)
			x->left = put(x->left, key, value);
		else if (key > x->key)
			x->right = put(x->right, key, value);
		else
			x->value = value;


		if (isRed(x->right) && !isRed(x->left))
			x = rotateLeft(x);
		if (isRed(x->left) && isRed(x->left->left))
			x = rotateRight(x);
		if (isRed(x->left) && isRed(x->right))
			flipcolors(x);

		x->size = 1 + size(x->left) + size(x->right);
		return x;
	}

	//function to check whether a link/node is red 
	bool isRed(Node *x)
	{
		if (x == NULL)
			return false;

		return x->color == RED;
	}

	//function to make a right leaning red link into a left leaning red link
	Node* rotateLeft(Node* x)
	{
		Node *temp = x->right;
		x->right = temp->left;
		temp->left = x;
		temp->color = x->color;
		x->color = RED;
		return temp;

	}

	//function to make a left leaning red link into a right leaning red link
	Node* rotateRight(Node* x)
	{
		Node *temp = x->left;
		x->left = temp->right;
		temp->right = x;
		temp->color = x->color;
		x->color = RED;
		return temp;
	}

	//function to flip colors of two red links(one left leaning and the other right leaning)
	void flipcolors(Node* x)
	{
		x->color = RED;
		x->left->color = BLACK;
		x->right->color = BLACK;
	}

	//function to traverse tree inorder and count number of red nodes and total nodes
	void inorder(Node *node)
	{
		if (node == NULL)
			return;

		inorder(node->left);
		if (node->color == 1)
			rcount++;

		cout << node->key << "---"<<node->color<<"----"<<node->size<<endl;

		inorder(node->right);

		tcount++;
	}

	//function to compute size of the tree
	int size(Node *node)
	{
		if (node == NULL)
			return 0;
		else
			return node->size;
	}

	//function to compute total internal path length
	int ipl(Node *node)
	{
		if (node == NULL)
			return 0;

		else
			return node->size + ipl(node->left) + ipl(node->right);
	}



public:
	void put(int key, int value)
	{
		root = put(root, key, value);
		root->color = BLACK;
	}
	void inorder()
	{
		Node* temp = root;
		inorder(temp);
	}
	int size()
	{
		return size(root);
	}
	int ipl()
	{
		return ipl(root);
	}
	bool isEmpty()
	{
		return size() == 0;
	}
	double getPercent()
	{
		double p;
		inorder();
		p = static_cast<double> (rcount) / tcount;
		return p * 100;
	}
	LLRBT()
	{

	}

};

int main()
{
	srand(time(0));
	const int size = 10000;
	
	double std_dev[size];


	//set the number of iterations
	const int num_of_iter = 1000;

	double avg_pl[num_of_iter];
	int i, j, k, temp, t;

	

	for (k = 1; k <= size; k++)
	{
		double total = 0;
		double avg = 0;

		int *arr = new int[k];

		for (j = 0; j < num_of_iter; j++)
		{
			LLRBT *l1 = new LLRBT();
			
			

			//generating ordered array
			for (i = 0; i < k; i++)
			{			
				arr[i]=i + 1;
			}

			//shuffling the values
			
			for (i = 0; i < k; i++)
			{
				t = rand() % k;
				temp = arr[t];
				arr[t] = arr[i];
				arr[i] = temp;

			}

			//creating tree with random insertions
			for (i = 0; i < k; i++)
			{
				l1->put(arr[i], i + 1);
			}

			avg_pl[j] = static_cast<double> (l1->ipl()) / l1->size();
			total += static_cast<double> (l1->ipl()) / l1->size();
			
			delete l1;
			
		}

		//averaging the average path lengths of different trees
		avg= static_cast<double> (total) / num_of_iter;
		cout << "Average path length for tree size " << k << " is: " << avg << endl;

		double total1 = 0;
		//computing standard deviation
		for (j = 0; j < num_of_iter; j++)
		{
			total1 += pow((avg - avg_pl[j]), 2);
		}
		std_dev[k-1]=sqrt(total1 / (num_of_iter - 1) );
		cout << "Standard deviation for tree size " << k << " is "<<std_dev[k-1]<<endl;
		delete[] arr;

		//putting data in a file
		ofstream file1("path_length_avg.txt", ios::app);
		file1 << avg << endl;

		//putting data in a file
		ofstream file2("path_length_std.txt", ios::app);
		file2 << std_dev[k - 1] << endl;
	}

	

	
	return 0;
}






		
		


