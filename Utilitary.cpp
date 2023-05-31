#include "Biblioteca.h"
#include <iostream>
using namespace std;

// enable user to input menu choice
Choice enterChoice() {
    // display available options
    system("cls");
    cout << "\nEnter your choice\n"
        << "1 - store a formatted text file of Library\n"
        << "    called \"print.txt\" for printing\n"
        << "2 - update a book\n"
        << "3 - add a new book\n"
        << "4 - delete a book\n"
        << "5 - end program\n? ";

    int menuChoice;
    cin >> menuChoice; // input menu selection from user
    return static_cast<Choice>(menuChoice);
}

// create formatted text file for printing
void createTextFile(fstream& readFromFile) {
    ofstream outPrintFile("Library.dat", ios::out); // create text file

    // exit program if ofstream cannot create file
    if (!outPrintFile) {
        cerr << "File could not be created." << endl;
        exit(EXIT_FAILURE);
    }

    // output column heads
    outPrintFile << left << setw(10) << "Account" << setw(16)
        << "Last Name" << setw(11) << "First Name" << right
        << setw(10) << "Balance" << endl;

    // set file-position pointer to beginning of readFromFile
    readFromFile.seekg(0);

    // read first record from record file
    Libro book;
    readFromFile.read(
        reinterpret_cast<char*>(&book), sizeof(Libro));

    // copy all records from record file into text file
    while (!readFromFile.eof()) {
        // write single record to text file
        if (book.getId() != 0) { // skip empty records
            outputLine(outPrintFile, book);
        }

        // read next record from record file                     
        readFromFile.read(
            reinterpret_cast<char*>(&book), sizeof(Libro));
    }
}

// update balance in record
void updateRecord(fstream& updateFile) {
    // obtain number of account to update
    int Id{ getId("Enter the ID of book to update") };

    // move file-position pointer to correct record in file          
    updateFile.seekg((Id - 1) * sizeof(Libro));

    // create record object and read first record from file
    Libro book;
    updateFile.read(reinterpret_cast<char*>(&book), sizeof(Libro));

    // update record
    if (book.getId() != 0) {
        outputLine(cout, book); // display the record

        // request user to specify transaction
        cout << "\nEnter Amount (+) (-): ";
        int amount; // charge or payment
        cin >> amount;

        // update record balance
        int oldAvailable = book.getAvailable();
        book.setAvailable(oldAvailable + amount);
        outputLine(cout, book); // display the record

        // move file-position pointer to correct record in file          
        updateFile.seekp((Id - 1) * sizeof(Libro));

        // write updated record over old record in file               
        updateFile.write(
            reinterpret_cast<const char*>(&book), sizeof(Libro));
    }
    else { // display error if account does not exist
        cerr << "Book #" << Id
            << " has no information." << endl;
    }
}

// create and insert record
void newRecord(fstream& insertInFile) {
    // obtain number of account to create
    int Id{ getId("Enter new ID ") };

    // move file-position pointer to correct record in file
    insertInFile.seekg((Id - 1) * sizeof(Libro));

    // read record from file
    Libro book;
    insertInFile.read(
        reinterpret_cast<char*>(&book), sizeof(Libro));

    // create record, if record does not previously exist
    if (book.getId() == 0) {
        string Title;
        string Author;
        int year;
        string Genre;
        int pages;
        int available;
        int borrowed;
        int reserved;

        // user enters last name, first name and balance
        cout << "Enter Title, Author, year, genre, pages, \n? ";
        cin >> setw(15) >> Title;
        cin >> setw(15) >> Author;
        cin >> year;
        cin >> setw(10) >> Genre;
        cin >> pages;
        cin >> available;
        cin >> borrowed;
        cin >> reserved;

        // use values to populate account values
        book.setTitle(Title);
        book.setAuthor(Author);
        book.setYear(year);
        book.setGenre(Genre);
        book.setPages(pages);
        book.setAvailable(available);
        book.setBorrowed(borrowed);
        book.setReserved(reserved);
        book.setId(Id);

        // move file-position pointer to correct record in file            
        insertInFile.seekp((Id - 1) * sizeof(Libro));

        // insert record in file                                        
        insertInFile.write(
            reinterpret_cast<const char*>(&book), sizeof(Libro));
    }
    else { // display error if account already exists
        cerr << "Book #" << Id
            << " already contains information." << endl;
    }
}

// delete an existing record
void deleteRecord(fstream& deleteFromFile) {
    // obtain number of account to delete
    int Id{ getId("Enter book to delete") };

    // move file-position pointer to correct record in file              
    deleteFromFile.seekg((Id - 1) * sizeof(Libro));

    // read record from file
    Libro book;
    deleteFromFile.read(
        reinterpret_cast<char*>(&book), sizeof(Libro));

    // delete record, if record exists in file
    if (book.getId() != 0) {
        Libro blankbook; // create blank record

        // move file-position pointer to correct record in file
        deleteFromFile.seekp((Id - 1) * sizeof(Libro));

        // replace existing record with blank record        
        deleteFromFile.write(
            reinterpret_cast<const char*>(&blankbook), sizeof(Libro));

        cout << "Account #" << Id << " deleted.\n";
    }
    else { // display error if record does not exist
        cerr << "Account #" << Id << " is empty.\n";
    }
}

// display single record
void outputLine(ostream& output, const Libro& record) {
    output << left << setw(10) << record.getId()
        << setw(16) << record.getTitle()
        << setw(16) << record.getAuthor()
        << setw(11) << record.getGenre()
        << setw(10) << setprecision(2) << right << fixed
        << showpoint << record.getPages() << endl;
}

// obtain account-number value from user
int getId(const char* const prompt) {
    int Id;

    // obtain account-number value
    do {
        cout << prompt << " (1 - 100): ";
        cin >> Id;
    } while (Id < 1 || Id > 100);

    return Id;
}

//const string FILENAME = "Library.txt";
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
void Libro::setId(int id) {this->id = id;}

string Libro::getTitle() const {return title;}
void Libro::setTitle(const string& title) {
	size_t length{title.size()};
	length = (length < 15 ? length : 14);
	title.copy(this->title, length);
	this->title[length] = '\0';
}

string Libro::getAuthor() const {return author;}
void Libro::setAuthor(const string& author) {
	size_t length{ author.size() };
	length = (length < 15 ? length : 14);
	author.copy(this->title, length);
	this->title[length] = '\0';
}

int Libro::getYear() const {return year;}
void Libro::setYear(int year) {this->year = year;}

string Libro::getGenre() const {return genre;}	
void Libro::setGenre(const string& genre) {
	size_t length{ genre.size() };
	length = (length < 15 ? length : 14);
	genre.copy(this->title, length);
	this->title[length] = '\0';
}

int Libro::getPages() const {return pages;}
void Libro::setPages(int pages) {this->pages = pages;}

int Libro::getQuantity() const {return quantity;}
void Libro::setQuantity(int quantity) {this->quantity = quantity;}

int Libro::getAvailable() const {return available;}
void Libro::setAvailable(int available) {this->available = available;}

int Libro::getBorrowed() const {return borrowed;}
void Libro::setBorrowed(int borrowed) {this->borrowed = borrowed;}

int Libro::getReserved() const {return reserved;}
void Libro::setReserved(int reserved) {this->reserved = reserved;}

ostream& operator<<(ostream& output, const Libro& book)
{
    output << left << setw(10) << book.getId() << setw(16) << book.getTitle() 
        << setw(16) << book.getAuthor() << setw(11) << book.getGenre() << setw(10) 
        << setprecision(2) << right << fixed << showpoint << book.getPages() << endl;
    return output;
}