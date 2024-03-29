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
			Node *newnode = new Node(key,value,RED);//new node creation
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
		
		cout << "node key---" <<node->key << "---node color---" << node->color << "---node size---" << node->size << endl;
		
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

	//function to get value associated with a key in ST
	int get(Node *x, int key)
	{
		while(x!=NULL)
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
		root = put(root, key,value);
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
	//set the range of key-value pairs from 1-range
	const int range = 7;
	//set the number of iterations
	const int num_of_iter = 1;
	int i, j, temp, t;



	vector<int> arr;
	for (i = 0; i < range; i++)
	{
		arr.push_back(i + 1);

	}

	for (j = 0; j < num_of_iter; j++)
	{
		ST *l2 = new ST();
		
		//shuffling the values
		
		for (i = 0; i < range; i++)
		{
			t = rand() % range;
			temp = arr[t];
			arr[t] = arr[i];
			arr[i] = temp;

		}

		cout << "Input:" << endl;
		//creating tree
		for (i = 0; i < range; i++)
		{
			cout << arr[i] << endl;
			l2->put(arr[i],i+1);
		}

		l2->inorder();
		cout << "Total internal path length is: " << l2->ipl() << endl;
		cout << "Tree size is: " << l2->size() << endl;
		delete l2;

	}


	return 0;
}

