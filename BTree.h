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
	return this->numOfSons == 0;
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
				for (auto j = this->numOfRecords - 1; j > i; j--) //Move all values one place to the left
					this->records[j] = this->records[j - 1];
				this->records[i] = record; //put the new record
			}
		}
	this->numOfRecords++;
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
	// TODO: fix
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
	// TODO: fix
}



template<class T>
T* BTree<T>::search(BNode* current, T key, int& counter)
{
	counter++;
	if (key > current->records[current->numOfRecords - 1]) //if the key is bigger than all the values
		return search(current->numOfSons[current->numOfRecords]); //go to the most left son
	else
		for (int i = 0; i < current->numOfRecords; i++) //go on the values
		{
			if (key != current->records[i]) //if the current value is not equal to the key
			{
				if (key < current->records[i]) //if the key smaller than the current value
					return search(current->numOfSons[i]); //search in the place "i" son
			}
			else
				return current->records;
		}
	return nullptr;
}

template<class T>
T* BTree<T>::search(T key) {
	int counter = 0;
	search(this->root, key, counter);
	cout << "The search involved scanning " << counter << " nodes" << endl;
	return nullptr;
}