// Name: Mareesh Kumar Issar
// Date of submission: April 02, 2019
// Course: 16:332:573, Data Structure and Algorithms
// Program name: Left Leaning Red Black Tree (calculating percentage of red nodes)
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
	Node(int key, int value, bool color)
	{
		this->key = key;
		this->value = value;
		this->left = NULL;
		this->right = NULL;
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
			Node *newnode = new Node(key,value,RED);//new node creation
			return newnode;
		}


		if (key < x->key)
			x->left = put(x->left, key,value);
		else if (key > x->key)
			x->right = put(x->right, key,value);
		else
			x->value = value;


		if (isRed(x->right) && !isRed(x->left))
			x=rotateLeft(x);
		if (isRed(x->left) && isRed(x->left->left))
			x = rotateRight(x);
		if (isRed(x->left) && isRed(x->right))
			flipcolors(x);
			
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
		
		//cout << node->key << "---"<<node->color<<endl;

		inorder(node->right);
	
		tcount++;
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
	double getPercent()
	{
		double p;
		inorder();
		p = static_cast<double> (rcount) / tcount;
		return p*100;
	}
	LLRBT()
	{

	}

};

int main()
{
	srand(time(0));
	const int size = 3;
	//set the range of key-value pairs from 1-range
	int range[size] = {10000,100000,1000000};


	//set the number of iterations
	const int num_of_iter = 100;

	int i, j, k, temp, t,l;

	vector<int> arr;

	for (k = 0; k < size; k++)
	{
		double total = 0;
		
		for (j = 0; j < num_of_iter; j++)
		{
			LLRBT *l1 = new LLRBT();
			
			//generating ordered array
			for (i = 0; i < range[k]; i++)
			{
				arr.push_back(i + 1);
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
				//cout << arr[i] << endl;
				l1->put(arr[i], i + 1);
			}

			total = total + l1->getPercent();
			delete l1;
		}

		//averaging the average percentage of red nodes present in different RB trees
		cout << "On average percentage of red nodes in a given RBT for tree size " << range[k] << " is: " << static_cast<double> (total) / num_of_iter << endl;
	}

	return 0;
}
	

	