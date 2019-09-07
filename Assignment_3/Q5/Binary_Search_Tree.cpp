// Name: Mareesh Kumar Issar
// Date of submission: April 02, 2019
// Course: 16:332:573, Data Structure and Algorithms
// Program name: BST rank and select operations
/* Source- 

https://algs4.cs.princeton.edu/32bst/BST.java.html

https://gist.github.com/mycodeschool/44e1a9183ab0e931f729

*/


#include <iostream>
#include <fstream>
#include <iomanip>



using namespace std;


struct Node
{
	int key;
	Node *left, *right;
	int size;
	Node(int key)
	{
		this->key = key;
		this->left = NULL;
		this->right = NULL;
		this->size = 1;
	}

};

class BST
{
	Node *root = NULL;//initially tree is empty

	//function to compute size of the tree
	int size(Node *node)
	{
		if (node == NULL)
			return 0;
		else
			return node->size;
	}

	//function to insert key into tree
	Node* put(Node* x, int key)
	{		
		if (x == NULL)
		{
			Node *newnode = new Node(key);//new node
			return newnode;
		}
			

		if (key < x->key)
			x->left = put(x->left, key);
		else if (key > x->key)
			x->right = put(x->right, key);
		else
			x->key = key;//overwrite

		x->size = 1 + size(x->left) + size(x->right);
		return x;

	}

	//function to compute number of keys less than given key
	int rank(int key, Node* x)
	{
		if (x == NULL)
			return 0;

		else if (key < x->key)
			return rank(key, x->left);
		else if (key > x->key)
			return 1 + size(x->left) + rank(key, x->right);
		else
			return size(x->left);
	}
	
	//function to select key of a given rank 
	Node* select(Node* x, int s)
	{
		if (x == NULL)
			return NULL;

		int t = size(x->left);
		if (t > s)
			return select(x->left, s);
		else if (t < s)
			return select(x->right, s - t - 1);
		else
			return x;

	}

	//function to get a key
	int get(Node* x, int key)
	{
		if (x == NULL)
			return NULL;

		if (key < x->key)
			return get(x->left, key);
		else if (key > x->key)
			return get(x->right, key);
		else
			return x->key;
	
	}
public:
	int size()
	{
		return size(root);
	}
	bool isEmpty()
	{
		return size() == 0;
	}
	int rank(int key)
	{
		return rank(key,root);
	}
	int select(int s)
	{
		Node *x= select(root,s);
		return x->key;
	}
	int get(int key)
	{
		return get(root, key);
	}
	void put(int key)
	{
		root = put(root, key);
	}

	
};

int main()
{
	int l;
	BST l1;

	//reading data from file 
	ifstream file1("select-data.txt"); // change input file name here, file should be in the same folder in which this cpp file is present
	if (file1.is_open())
	{
		while (file1 >> l)
		{
			l1.put(l);//creating BST
		}

		file1.close();
	}

	else
	{
		cout << "Error in opening file" << endl;
	}

	cout << "The value for select(7) is " << l1.select(7) << endl;
	cout << "The value for rank(7) is " << l1.rank(7)<<endl;
	

	return 0;
}

