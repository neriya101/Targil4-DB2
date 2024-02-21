#pragma once
#include<iostream>
using namespace std;
class Book
{
private:
	int catalogNumber;
	int shelf;
	bool available;
public:
	int getKey() { return catalogNumber; }
	Book(int catalog = 0, int _self = 0);
	bool borrowBook(int catalog);
	bool returnBook(int catalog);
	// TODO: fix operators
	bool operator<(Book b) { return this->catalogNumber < b.catalogNumber ? true : false; }
	bool operator>(Book b) { return this->catalogNumber > b.catalogNumber ? true : false; }
	bool operator<=(Book b) { return this->catalogNumber <= b.catalogNumber ? true : false; }
	bool operator==(Book b) { return this->catalogNumber == b.catalogNumber ? true : false; }
	bool operator!=(Book b) { return this->catalogNumber != b.catalogNumber ? true : false; }
	friend ostream& operator<<(ostream& os, Book b);
	friend istream& operator>>(istream& is, Book& b);
};

