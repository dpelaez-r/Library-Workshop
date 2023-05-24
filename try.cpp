#include "Biblioteca.h"
#include <iostream>
using namespace std;

const string FILENAME = "Library.txt";
Libro::Libro(int id, const string& title, const string& author, int year, const string& genre, int pages, int quantity, int avaible, int borrowed, int reserved)
{
	setId(id);
	setTitle(title);
	setAuthor(author);
	setYear(year);
	setGenre(genre);
	setPages(pages);
	setQuantity(quantity);
	setAvailable(available);
	setBorrowed(borrowed);
	setReserved(reserved);
}
int Libro::getId() const { return id; }
void Libro::setId(int id) { this->id = id; }

string Libro::getTitle() const { return title; }
void Libro::setTitle(const string& title) {
	size_t length{ title.size() };
	length = (length < 15 ? length : 14);
	title.copy(this->title, length);
	this->title[length] = '\0';


}

string Libro::getAuthor() const { return author; }
void Libro::setAuthor(const string& author) {
	size_t length{ author.size() };
	length = (length < 15 ? length : 14);
	author.copy(this->title, length);
	this->title[length] = '\0';
}

int Libro::getYear() const { return year; }
void Libro::setYear(int year) { this->year = year; }

string Libro::getGenre() const { return genre; }
void Libro::setGenre(const string& genre) {
	size_t length{ genre.size() };
	length = (length < 15 ? length : 14);
	genre.copy(this->title, length);
	this->title[length] = '\0';
}

int Libro::getPages() const { return pages; }
void Libro::setPages(int pages) { this->pages = pages; }

int Libro::getQuantity() const { return quantity; }
void Libro::setQuantity(int quantity) { this->quantity = quantity; }

int Libro::getAvailable() const { return available; }
void Libro::setAvailable(int available) { this->available = available; }

int Libro::getBorrowed() const { return borrowed; }
void Libro::setBorrowed(int borrowed) { this->borrowed = borrowed; }

int Libro::getReserved() const { return reserved; }
void Libro::setReserved(int reserved) { this->reserved = reserved; }
