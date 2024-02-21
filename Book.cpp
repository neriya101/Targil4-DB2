#include "Book.h"

Book::Book(int catalog, int _shelf)
{
	this->catalogNumber = catalog;
	this->shelf = _shelf;
	this->available = true;
}

bool Book::borrowBook(int catalog)
{
	if(available)
	{
		available = false;
		cout << "Successfully found the book " << catalogNumber << " on shelf " << shelf << " and borrowed it" << endl;
	}
	else
		cout << "Error! The book " << catalogNumber << " is already borrowed!" << endl;
	return true;
}

bool Book::returnBook(int catalog)
{
	if (!available)
	{
		available = true;
		cout << "Successfully returned the book " << catalogNumber << " to shelf " << shelf << endl;
	}
	else
		cout << "Error! The book " << catalogNumber << " is not borrowed!" << endl;
	return true;
}

ostream& operator<<(ostream& os, Book b)
{
	os << "{" << b.catalogNumber << ", " << b.shelf << ", ";
	os << (b.available ? "available" : "borrowed") << "}";
	return os;
}

istream& operator>>(istream& is, Book& b)
{
	is >> b.catalogNumber >> b.shelf;
	return is;
}
