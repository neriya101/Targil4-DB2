#include "Library.h"

Library::Library(string path, LibraryDataStructure<Book>& _ds) : ds(_ds) {
	ifstream inputFile(path); // Open the file for reading

	if (!inputFile.is_open()) {
		std::cerr << "Error: Unable to open file: " << path << std::endl;
		return;
	}

	Book book;
	// Read books from the file using the input operator >>
	while (inputFile >> book) {
		ds.insert(book); // Add the book to the vector
	}
	inputFile.close();
}


bool Library::borrowBook(int catalogNumber) {
	Book* book = ds.search(catalogNumber);
	int i = 0;
	if (book == nullptr) {
		cout << "Error! The book " << catalogNumber << " does not exist!" << endl;
		return false;
	}
	while (book[i].getKey() != catalogNumber)
		i++;
	return book[i].borrowBook(catalogNumber);
}

bool Library::returnBook(int catalogNumber) {
	Book* book = ds.search(catalogNumber);
	int i = 0;
	if (book == nullptr) {
		cout << "Error! The book " << catalogNumber << " does not exist!" << endl;
		return false;
	}
	while (book[i].getKey() != catalogNumber)
		i++;
	return book[i].returnBook(catalogNumber);

}

void Library::validateDataStructure() {
	ds.inorder();
}
