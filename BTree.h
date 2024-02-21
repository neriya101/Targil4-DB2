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
	T* search(BNode* current, int key, int& counter);
public:
	BTree(int degree); //ctor
	~BTree(); //dtor
	void inorder();//print the tree inorder.
	void insert(T record);
	T* search(int key);//search for record and print the number of visited nodes.


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
	if (this->numOfRecords == 0)
		this->records[0] = record;
	else if (this->records[this->numOfRecords - 1] < record)
		this->records[this->numOfRecords] = record;
	else
		for (auto i = 0; i < this->numOfRecords; i++)
		{
			if (this->records[i] > record)
			{
				for (auto j = this->numOfRecords - 1; j > i; j--)
					this->records[j] = this->records[j - 1];
				this->records[i] = record;
			}
		}
	this->numOfRecords++;
}

template<class T>
void BTree<T>::BNode::remove(T record)
{
	// TODO: fix
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
	// TODO: fix
}
template<class T>
void BTree<T>::inorder()
{
	// TODO: fix
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
	// TODO: fix
}
template<class T>
void BTree<T>::inorder(BNode* current)
{
	// TODO: fix
}

template<class T>
typename BTree<T>::BNode* BTree<T>::findAddNode(BNode* current, T record)
{
	// TODO: fix
	return nullptr;
}

template <class T>
void BTree<T>::split(BNode* current)
{
	// TODO: fix
}



template<class T>
T* BTree<T>::search(BNode* current, int key, int& counter)
{
	// TODO: fix
	return nullptr;
}

template<class T>
T* BTree<T>::search(int key) {
	int counter = 0;
	// TODO: fix
	cout << "The search involved scanning " << counter << " nodes" << endl;
	return nullptr;
}
