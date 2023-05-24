#ifndef Biblioteca.h
#define Biblioteca.h
#include <iostream>
#include <fstream>
#include <vector>
#include <string>


using namespace std;
class Libro {
private:
	char title[15];
	char author[15];
	int year;
	char genre[10];
	int pages;
	int id;
	int quantity;
	int available;
	int borrowed;
	int reserved;
public:
	void setTitle(const string&);
	void setAuthor(const string&);
	void setYear(int);
	void setGenre(const string&);
	void setPages(int);
	void setId(int);
	void setQuantity(int);
	void setAvailable(int);
	void setBorrowed(int);
	void setReserved(int);
};

class library {
	private:

};

#endif // !Biblioteca.h


/*class Library
{
	private:
		vector <Libro> books;
		int size;
		int capacity;
	public:
		Library(int capacity);
		void addBook(const Libro& book);
		void deleteBook(int id);
		void searchbyTitle(const string& title);
		void searchbyAuthor(const string& author);
		void searchbyYear(int year);
		void searchbyGenre(const string& genre);
		void modifyBook(int id);
		void borrowBook(int id);
		void showAvailable();
		void showBorrowed();
		void showReserved();
		~Library();
};*/