#pragma once
#include<iostream>
#include "LibraryDataStructure.h"
using namespace std;

template<class T>
class BTree : public LibraryDataStructure<T>
{
public:
	class BNode
	{
	public:
		int m;		//max num of records in node +1.
		T* records; //array size m.
		BNode** sons; //array of pointers to node sons size m+1.
		BNode* parent; // pointer to parent node.
		int numOfRecords; //number of saved records.
		int numOfSons; //number of node sons.
		BNode(int _m); //ctor
		~BNode(); //dtor
		bool isLeaf();
		void insert(T record);
		void remove(T record);
		void printKeys(); //print the keys of the node
	};
	int m; //rank of tree.
	BNode* root; //pointer to root node.

	void clear(BNode* current); //delete all tree post order.
	void inorder(BNode* current);
	BNode* findAddNode(BNode* current, T record);
	void split(BNode* current);
	T* search(BNode* current, T key, int& counter);
public:
	BTree(int degree); //ctor
	~BTree(); //dtor
	void inorder();//print the tree inorder.
	void insert(T record);
	T* search(T key);//search for record and print the number of visited nodes.


};
////////////////////////////////////////////////////////////////

template<class T>
BTree<T>::BNode::BNode(int _m)
{
	this->m = _m;
	this->records = new T[m];
	this->sons = new BNode * [m + 1];
	this->parent = nullptr;
	this->numOfRecords = 0;
	this->numOfSons = 0;
}

template<class T>
BTree<T>::BNode::~BNode()
{
	this->m = 0;
	this->records = nullptr;
	this->sons = nullptr;
	this->parent = nullptr;
	this->numOfRecords = 0;
	this->numOfSons = 0;
}

template<class T>
bool BTree<T>::BNode::isLeaf()
{
	return this != nullptr ? this->numOfSons == 0 : true;
}

template<class T>
void BTree<T>::BNode::insert(T record)
{
	if (this->numOfRecords == 0) //if there is no values yet then add one to the start
		this->records[0] = record;
	else if (this->records[this->numOfRecords - 1] < record) //if the new value need to go to the end
		this->records[this->numOfRecords] = record;
	else
		for (auto i = 0; i < this->numOfRecords; i++) //Other case, go on the array
		{
			if (this->records[i] > record)//search if the record is bigger the the current one
			{
				for (auto j = this->numOfRecords; j > i; j--) //Move all values one place to the right
					this->records[j] = this->records[j - 1];
				this->records[i] = record; //put the new record
				break;
			}
		}
	this->numOfRecords++;
	for (int i = 0; i < this->numOfRecords; i++)
	{
		cout << this->records[i];
	}
	cout << endl;
}

template<class T>
void BTree<T>::BNode::remove(T record)
{
	for (auto i = 0; i < this->numOfRecords; i++)
	{
		if (this->records[i] == record) //if the value is find
		{
			for (auto j = i; j > this->numOfRecords - 1; j--) //Move all values one place to the right
				this->records[j] = this->records[j + 1];
			this->numOfRecords--;
		}
	}
}

template<class T>
void BTree<T>::BNode::printKeys()
{
	cout << '(';
	for (int i = 0; i < numOfRecords - 1; i++)
		cout << records[i].getKey() << ",";
	cout << records[numOfRecords - 1].getKey() << ')' << endl;
}


template<class T>
BTree<T>::BTree(int degree) :m(degree), root(nullptr)
{}

template<class T>
BTree<T>::~BTree()
{
	clear(this->root);
}
template<class T>
void BTree<T>::inorder()
{
	inorder(this->root);
}

template<class T>
void BTree<T>::insert(T record)
{
	BNode* temp; //will be the node where we want to insert.
	if (!this->root)
		this->root = new BNode(this->m);
	temp = this->root;
	BNode* parent = nullptr; //will save the parent node for future use.
	while (!temp->isLeaf())
	{
		if (record > temp->records[temp->numOfRecords - 1]) //if the record is higher than every key in the node.
		{
			parent = temp;
			temp = temp->sons[temp->numOfRecords]; //the next node will be the highest node.
		}
		else
		{
			for (auto i = 0; i < temp->numOfRecords; i++) //run on the current node
			{
				if (record < temp->records[i]) //searching the node
				{
					parent = temp;
					temp = temp->sons[i];
					break;
				}
			}
		}
	}
	//temp is now the leaf we want to insert into.
	temp->insert(record);
	temp->parent = parent;
	if (temp->numOfRecords == this->m) //if the node is full we need to split the node.
		this->split(temp);
}

//private recursive help fuctions
template<class T>
void BTree<T>::clear(BNode* current)
{
	if (current) //if exits
	{
		for (int i = 0; i < current->numOfSons; i++) //go on and delete in postorder style
			clear(current->sons[i]);
		delete current;
	}
}
template<class T>
void BTree<T>::inorder(BNode* current)
{
	if (current)
	{
		if (current->numOfSons == 0)
			current->printKeys();
		else
			for (int i = 0; i < current->numOfSons; i++) //go on and print in inorder style
			{
				inorder(current->sons[i]);
				current->printKeys();
			}
	}
}

template<class T>
typename BTree<T>::BNode* BTree<T>::findAddNode(BNode* current, T record)
{
	int counter = 0;
	if (current)
		return search(current, record, counter);
	else return nullptr;
}

template <class T>
void BTree<T>::split(BNode* current)
{
	if (current->parent == nullptr)
		current->parent = new BNode(this->m);
	int removeFrom = 0;
	T temp = current->records[current->numOfRecords / 2]; //temp will hold the record we need to split from
	current->remove(current->records[current->numOfRecords / 2]); //remove the record we want to split
	current->parent->insert(temp); //insert the record to the paernt
	for (auto i = 0; i < current->parent->numOfSons; i++)
		if (current->parent->records[i] == temp)
		{
			removeFrom = i;
			break;
		}
	for (auto i = current->parent->numOfSons; i > removeFrom + 1; i--)
		current->parent->sons[i] = current->parent->sons[i - 1];
	BNode* right = new BNode(this->m);
	BNode* left = new BNode(this->m);
	for (auto i = current->numOfRecords; i > current->numOfRecords / 2; i--)
		right->insert(current->records[i]);
	for (auto i = current->numOfRecords / 2 - 1; i >= 0; i--)
		left->insert(current->records[i]);
	if (current->numOfSons != 0)
	{
		if (current->numOfSons == this->m + 1) //adjusment when the number of sons is exceed
			current->numOfSons--;
		int c = 0;
		for (auto i = 0; i < (current->numOfSons + 1) / 2; i++)
		{
			left->numOfSons++;
			left->sons[i] = current->sons[i];
		}
		for (auto i = (current->numOfSons + 1) / 2; i < current->numOfSons + 1; i++, c++)
		{
			right->numOfSons++;
			right->sons[c] = current->sons[i];
		}
	}
	current->parent->sons[removeFrom] = left;
	current->parent->sons[removeFrom + 1] = right;
	if (current->parent->numOfSons == 0)
	{
		this->root = current->parent;
		current->parent->numOfSons = 2;
	}
	else
		current->parent->numOfSons++;
	if (current->parent->numOfRecords == m)
		split(current->parent);
}



template<class T>
T* BTree<T>::search(BNode* current, T key, int& counter)
{
	counter++;
	if (key > current->records[current->numOfRecords - 1]) //if the key is bigger than all the values
		return search(current->sons[current->numOfRecords], key, counter); //go to the most right son
	else
		for (int i = 0; i < current->numOfRecords; i++) //go on the values
		{
			if (key != current->records[i]) //if the current value is not equal to the key
			{
				if (key < current->records[i]) //if the key smaller than the current value
					return search(current->sons[i], key, counter); //search in the place "i" son
			}
			else
				return current->records;
		}
	return nullptr;
}

template<class T>
T* BTree<T>::search(T key) {
	int counter = 0;
	T* searchedNode = search(this->root, key, counter);
	cout << "The search involved scanning " << counter << " nodes" << endl;
	return searchedNode;
}