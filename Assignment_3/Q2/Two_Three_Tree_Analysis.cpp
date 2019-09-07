// Name: Mareesh Kumar Issar
// Date of submission: April 02, 2019
// Course: 16:332:573, Data Structure and Algorithms
// Program name: Two Three Tree- Symbol Table API
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

class ST
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
		{
			x->left = put(x->left, key, value);
			if (isRed(x) || isRed(x->right))//two touching red links are not allowed
				x->left->color = BLACK;

		}

		else if (key > x->key)
		{
			x->right = put(x->right, key, value);
			if (isRed(x) || isRed(x->left))//two touching red links are not allowed
				x->right->color = BLACK;
		}

		else
			x->value = value;

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

	//function to traverse tree inorder and count number of red nodes and total nodes
	void inorder(Node *node)
	{
		if (node == NULL)
			return;

		inorder(node->left);
		if (node->color == 1)
			rcount++;

		cout << "node key---" << node->key << "---node color---" << node->color << "---node size---" << node->size << endl;

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


	//function to compute total internal path length(considering only black nodes)
	int black_ipl(Node *node)
	{
		int c;
		if (node == NULL)
			return 0;

		c= node->size + black_ipl(node->left) + black_ipl(node->right);

		if (isRed(node))
			c = c - node->size;

		return c;
	}

	//function to get value associated with a key in ST
	int get(Node *x, int key)
	{
		while (x != NULL)
		{
			if (key < x->key)
				x = x->left;
			else if (key > x->key)
				x = x->right;
			else
				return x->value;
		}
		return NULL;
	}


public:
	void put(int key, int value)
	{
		root = put(root, key, value);
		root->color = BLACK;
	}
	int size()
	{
		return size(root);
	}
	int ipl()
	{
		return ipl(root);
	}
	int black_ipl()
	{
		return black_ipl(root);
	}
	bool isEmpty()
	{
		return size() == 0;
	}
	int get(int key)
	{
		return get(root, key);
	}
	bool contains(int key)
	{
		return get(key) != NULL;
	}
	void inorder()
	{
		Node* temp = root;
		inorder(temp);
	}
	ST()
	{

	}
};

int main()
{
	srand(time(0));
	const int size = 13;
	//set the range of key-value pairs from 1-range
	int range[size] = {1,3,7,15,31,63,127,255,511,1023,2047,4095,8191};
	

	//set the number of iterations
	const int num_of_iter = 100;

	int i, j, k, temp, t;
	
	vector<int> arr;

	for (k = 0;k<size; k++)
	{
		double avg_sorted = 0;
		double avg_random = 0;
		
		for (j = 0; j < num_of_iter; j++)
		{
			ST *l1 = new ST();
			ST *l2 = new ST();

			//generating ordered array
			for (i = 0; i < range[k]; i++)
			{
				arr.push_back(i + 1);
			}

			//creating tree with sorted insertions
			for (i = 0; i < range[k]; i++)
			{
				l1->put(arr[i], i + 1);
			}

			//shuffling the values
			
			for (i = 0; i < range[k]; i++)
			{
				t = rand() % range[k];
				temp = arr[t];
				arr[t] = arr[i];
				arr[i] = temp;

			}

			//creating tree with random insertions
			for (i = 0; i < range[k]; i++)
			{
				l2->put(arr[i], i + 1);
			}
			

			//computing avg path for each tree considering both red and black links
		//	avg_sorted = avg_sorted + static_cast<double> (l1->ipl()) / range[k];
		//	avg_random = avg_random + static_cast<double> (l2->ipl()) / range[k];

			//for computing avg path for each tree considering only black links
			avg_sorted = avg_sorted + static_cast<double> (l1->black_ipl()) / range[k];
			avg_random = avg_random + static_cast<double> (l2->black_ipl()) / range[k];

			delete l1;
			delete l2;
			arr.clear();
		}

		//averaging the average path lengths of different trees
		avg_sorted = static_cast<double> (avg_sorted) / num_of_iter;
		cout << "Average path length for sorted insertion for tree size " << range[k] << " is: " << avg_sorted << endl;
		avg_random = static_cast<double> (avg_random) / num_of_iter;
		cout << "Average path length for random insertion for tree size "<< range[k]<<" is: "<< avg_random << endl;

		//putting data in a file
		ofstream file1("avg_sorted_black.txt",ios::app);
		file1 << avg_sorted << endl;
	
		//putting data in a file
		ofstream file2("avg_random_black.txt", ios::app);
		file2 << avg_random << endl;
	}
	return 0;
}

