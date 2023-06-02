#ifndef Biblioteca_h
#define Biblioteca_h
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cstdlib>

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
	friend ostream& operator<<(ostream&, const Libro&);
};

enum class Choice { PRINT = 1, UPDATE = 2, NEW = 3, DELETE = 4, SEARCH = 5, END = 6};

Choice enterChoice();
void createTextFile(fstream&);
void updateRecord(fstream&);
void newRecord(fstream&);
void deleteRecord(fstream&);
void searchBook(fstream&);
void outputLine(ostream&, const Libro&);
int getId(const char* const);


#endif // !Biblioteca_h

