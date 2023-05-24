#ifndef Biblioteca.h
#define Biblioteca.h
#include <iostream>
#include <fstream>
#include <string>


using namespace std;
class Libro {
private:
	int id;
	char title[15];
	char author[15];
	int year;
	char genre[10];
	int pages;
	int quantity;
	int available;
	int borrowed;
	int reserved;
public:
	Libro(int = 0, const string& = "", const string& = "", int = 0, const string& = "", int = 0, int = 0, int=0, int = 0, int= 0);

	void setId(int);
	int getId() const;

	void setTitle(const string&);
	string getTitle() const;
		;
	void setAuthor(const string&);
	string getAuthor() const;

	void setYear(int);
	int getYear() const;

	void setGenre(const string&);
	string getGenre() const;

	void setPages(int);
	int getPages() const;

	void setQuantity(int);
	int getQuantity() const;

	void setAvailable(int);
	int getAvailable() const;

	void setBorrowed(int);
	int getBorrowed() const;

	void setReserved(int);
	int getReserved() const;
};

#endif // !Biblioteca.h


