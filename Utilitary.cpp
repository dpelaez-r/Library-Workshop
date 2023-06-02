#include "Biblioteca.h"
#include <iostream>
using namespace std;



// enable user to input menu choice
Choice enterChoice() {
    system("cls");
    // display available options
    cout << "Enter your choice\n"
        << "1 - store a formatted text file of Library\n"
        << "    called \"print.txt\" for printing\n"
        << "2 - update a book\n"
        << "3 - add a new book\n"
        << "4 - delete a book\n"
        << "5 - search book\n"
        << "6 - end program\n? ";

    int menuChoice;
    cin >> menuChoice; // input menu selection from user
    return static_cast<Choice>(menuChoice);
}

// create formatted text file for printing
void createTextFile(fstream& readFromFile) {
    system("cls");
    ofstream outPrintFile("Library.dat", ios::out); // create text file

    // exit program if ofstream cannot create file
    if (!outPrintFile) {
        cerr << "File could not be created." << endl;
        exit(EXIT_FAILURE);
    }

    // output column heads
    outPrintFile << left << setw(10) << "Id"
        << setw(16) << "Title"
        << setw(16) << "Author"
        << setw(11) << "Genre"
        << setw(10) << "Year"
        << setw(10) << "Pages"
        << setw(10) << "Quantity"
        << setw(10) << "Available"
        << setw(10) << "Borrowed"
        << setw(10) << "Reserved" << endl;

    // set file-position pointer to beginning of readFromFile
    readFromFile.seekg(0);

    // read first record from record file
    Libro book;
    readFromFile.read(reinterpret_cast<char*>(&book), sizeof(Libro));

    // copy all records from record file into text file
    while (!readFromFile.eof()) {
        // write single record to text file
        if (book.getId() != 0) { // skip empty records
            outputLine(outPrintFile, book);
        }

        // read next record from record file                     
        readFromFile.read(reinterpret_cast<char*>(&book), sizeof(Libro));
    }
}

// update balance in record
void updateRecord(fstream& updateFile) {
    system("cls");

    bool run = true;
    while (run){
        system("cls");
        int Id{ getId("Enter the ID of book to update") };
        Libro book;
        // obtain number of account to update
        cout << "1) Update quantity\n2) Borrow book\n3) Reserve book\n4) Finish updating\n";
        int choice;
        cin >> choice;
        switch (choice) {
        case 1:
            // move file-position pointer to correct record in file          
            updateFile.seekg((Id - 1) * sizeof(Libro));

            // create record object and read first record from file
            updateFile.read(reinterpret_cast<char*>(&book), sizeof(Libro));

                // update record
                if (book.getId() != 0) {
                    outputLine(cout, book); // display the record
                    // request user to specify transaction
                    cout << "\nEnter quantity of new books: ";
                    int amount; // amount of books
                    cin >> amount;
                    // update book record
                    int oldQuantity = book.getQuantity();
                    int oldAvailable = book.getAvailable();
                    book.setQuantity(oldQuantity + amount);
                    book.setAvailable(oldAvailable + amount);
                    outputLine(cout, book); // display the record
                    cout << "Press Enter to continue...";
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cin.get();

                    // move file-position pointer to correct record in file          
                    updateFile.seekp((Id - 1) * sizeof(Libro));

                    // write updated record over old record in file               
                    updateFile.write(
                        reinterpret_cast<const char*>(&book), sizeof(Libro));
                }
                else { // display error if account does not exist
                    cerr << "Book #" << Id
                        << " has no information." << endl;
                    cout << "Press Enter to continue...";
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cin.get();
                }
        break;
        case 2:
            // move file-position pointer to correct record in file          
            updateFile.seekg((Id - 1) * sizeof(Libro));
            
            updateFile.read(reinterpret_cast<char*>(&book), sizeof(Libro));

            // update record
            try {
                if (book.getId() != 0) {
                    outputLine(cout, book); // display the record
                    // request user to specify transaction
                    cout << "\nEnter the amount of books you want to borrow: ";
                    int amount; // amount of books
                    cin >> amount;
                    // update book record

                    // Check if available quantity is sufficient for the borrow request
                    if (amount <= book.getAvailable()) {
                        int oldQuantity = book.getBorrowed();
                        book.setBorrowed(oldQuantity + amount);
                        int oldAvailable = book.getAvailable();
                        book.setAvailable(oldAvailable - (book.getBorrowed() + book.getReserved()));
                        outputLine(cout, book); // display the record
                        cout << "Press Enter to continue...";
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        cin.get();
                        // move file-position pointer to correct record in file          
                        updateFile.seekp((Id - 1) * sizeof(Libro));

                        // write updated record over old record in file               
                        updateFile.write(reinterpret_cast<const char*>(&book), sizeof(Libro));
                    }
                    else {
                        throw runtime_error("Insufficient copies available for borrowing");
                    }
                }
                else { // display error if account does not exist
                    cerr << "Book #" << Id << " has no information." << endl;
                }
            }
            catch (const exception& ex) {
                cerr << "Exception caught: " << ex.what() << endl;
                cout << "Press Enter to continue...";
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cin.get();
            }

            break;
        case 3:
            // move file-position pointer to correct record in file          
            updateFile.seekg((Id - 1) * sizeof(Libro));

            // create record object and read first record from file
            //Libro book;
            updateFile.read(reinterpret_cast<char*>(&book), sizeof(Libro));

            // update record
            try{
                if (book.getId() != 0) {
                    outputLine(cout, book); // display the record
                    // request user to specify amount
                    cout << "\nEnter the amount of books you want to borrow: ";
                    int amount; // amount of books
                    cin >> amount;
                    
                    // Check if available quantity is sufficient for the borrow request
                    if (amount <= book.getAvailable()) {
                        int oldQuantity = book.getReserved();
                        book.setReserved(oldQuantity + amount);
                        int oldAvailable = book.getAvailable();
                        book.setAvailable(oldAvailable - (book.getBorrowed() + book.getReserved()));
                        outputLine(cout, book); // display the record
                        cout << "Press Enter to continue...";
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        cin.get();
                        // move file-position pointer to correct record in file          
                        updateFile.seekp((Id - 1) * sizeof(Libro));
                        // write updated record over old record in file               
                        updateFile.write(reinterpret_cast<const char*>(&book), sizeof(Libro));
                    }
                    else {
                        throw std::runtime_error("Insufficient copies available for borrowing");
                    }

                    // write updated record over old record in file               
                    updateFile.write(reinterpret_cast<const char*>(&book), sizeof(Libro));
                }
                else { // display error if account does not exist
                    cerr << "Book #" << Id
                        << " has no information." << endl;
                    cout << "Press Enter to continue...";
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cin.get();
                }
            }
            catch(const exception& ex){ // display error if amount is too big
                cerr << "Exception caught: " << ex.what() << endl;
                cout << "Press Enter to continue...";
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cin.get();
            }
                    
        break;
        case 4: //end updating books
            run = false;
			break;
        default:
            cout << "Invalid choice";

    }
}

}

// create and insert record
void newRecord(fstream& insertInFile) {
    system("cls");
    // obtain number of account to create
    int Id{ getId("Enter new ID ") };

    // move file-position pointer to correct record in file
    insertInFile.seekg((Id - 1) * sizeof(Libro));

    // read record from file
    Libro book;
    insertInFile.read(reinterpret_cast<char*>(&book), sizeof(Libro));

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

        // user does entries
        cout << "Enter Title, Author, genre, year, pages, available, borrowed, reserved";
        cout << "\n";
        cin.ignore();
        getline(cin, Title);
       // cin.ignore();
        getline(cin, Author);
        //cin.ignore();
        getline(cin, Genre);
        /*cin.ignore();*/
        cin >> year;
        cin.ignore();
        cin >> pages;
        cin.ignore();
        cin >> available;
        cin.ignore();
        cin >> borrowed;
        cin.ignore();
        cin >> reserved;

        // use values to populate account values
        book.setId(Id);
        book.setTitle(Title);
        book.setAuthor(Author);
        book.setGenre(Genre);
        book.setYear(year);
        book.setPages(pages);
        book.setQuantity(available + borrowed + reserved);
        book.setAvailable(available);
        book.setBorrowed(borrowed);
        book.setReserved(reserved);
        

        // move file-position pointer to correct record in file            
        insertInFile.seekp((Id - 1) * sizeof(Libro));

        // insert record in file                                        
        insertInFile.write(reinterpret_cast<const char*>(&book), sizeof(Libro));
    }
    else { // display error if account already exists
        cerr << "Book #" << Id
            << " already contains information." << endl;
        cout << "Press Enter to continue...";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.get();

    }
}

// delete an existing record
void deleteRecord(fstream& deleteFromFile) {
    system("cls");
    // obtain number of account to delete
    int Id{ getId("Enter book to delete") };

    // move file-position pointer to correct record in file              
    deleteFromFile.seekg((Id - 1) * sizeof(Libro));

    // read record from file
    Libro book;
    deleteFromFile.read(reinterpret_cast<char*>(&book), sizeof(Libro));

    // delete record, if record exists in file
    if (book.getId() != 0) {
        Libro blankbook; // create blank record

        // move file-position pointer to correct record in file
        deleteFromFile.seekp((Id - 1) * sizeof(Libro));

        // replace existing record with blank record        
        deleteFromFile.write(reinterpret_cast<const char*>(&blankbook), sizeof(Libro));

        cout << "Book #" << Id << " deleted.\n";
    }
    else { // display error if record does not exist
        cerr << "Book #" << Id << " is empty.\n";
        cout << "Press Enter to continue...";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.get();
    }
}

// search for book
void searchBook(fstream& searchbook) {
    system("cls");
    // obtain number of account to delete
    int Id{ getId("Enter book to delete") };

    // move file-position pointer to correct record in file              
    searchbook.seekg((Id - 1) * sizeof(Libro));

    // read record from file
    Libro book;
    searchbook.read( reinterpret_cast<char*>(&book), sizeof(Libro));
    if (book.getId() != 0) {
        outputLine(cout, book);
        cout << "Press Enter to continue...";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.get();
    }
    else { // display error if account does not exist
        cerr << "Book #" << Id
            << " has no information." << endl;
    }
}

// display single record
void outputLine(ostream& output, const Libro& record) {
    system("cls");
    output << left << setw(10) << "Id" 
        << setw(16) << "Title" 
        << setw(16)<< "Author" 
        << setw(11) << "Genre"
        << setw(10) << "Year" 
        << setw(10) << "Pages" 
        << setw(10) << "Quantity" 
        << setw(10) << "Available" 
        << setw(10) << "Borrowed"
        << setw(10) << "Reserved" << endl;

    output << left << setw(10) << record.getId()
        << setw(16) << record.getTitle()
        << setw(16) << record.getAuthor()
        << setw(11) << record.getGenre()
        << setw(10) << record.getYear()
        << setw(10) << record.getPages()
        << setw(10) << record.getQuantity()
        << setw(10) << record.getAvailable()
        << setw(10) << record.getBorrowed()
        << setw(10) << record.getReserved()
        << setw(10) << setprecision(2) << right << fixed
        << showpoint << endl;
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
    setGenre(genre);
    setYear(year);
	setPages(pages);
	setQuantity(quantity);
	setAvailable(available);
	setBorrowed(borrowed);
	setReserved(reserved);
}
int Libro::getId() const { return id; }
void Libro::setId(int Id) {
    id = Id;}

string Libro::getTitle() const {return title;}
void Libro::setTitle(const string& titleString) {
	size_t length{titleString.size()};
	length = (length < 15 ? length : 14);
	titleString.copy(title, length);
	title[length] = '\0';
}

string Libro::getAuthor() const {return author;}
void Libro::setAuthor(const string& authorString) {
	size_t length{ authorString.size() };
	length = (length < 15 ? length : 14);
	authorString.copy(author, length);
	author[length] = '\0';
}

int Libro::getYear() const {return year;}
void Libro::setYear(int Year) {year = Year;}

string Libro::getGenre() const {return genre;}	
void Libro::setGenre(const string& genreString) {
	size_t length{ genreString.size() };
	length = (length < 10 ? length : 9);
	genreString.copy(genre, length);
	genre[length] = '\0';
}

int Libro::getPages() const {return pages;}
void Libro::setPages(int Pages) { pages = Pages;}

int Libro::getQuantity() const {return quantity;}
void Libro::setQuantity(int Quantity) {quantity = Quantity;}

int Libro::getAvailable() const {return available;}
void Libro::setAvailable(int Available) {available = Available;}

int Libro::getBorrowed() const {return borrowed;}
void Libro::setBorrowed(int Borrowed) {borrowed = Borrowed;}

int Libro::getReserved() const {return reserved;}
void Libro::setReserved(int Reserved) {reserved = Reserved;}

ostream& operator<<(ostream& output, const Libro& book)
{
    output << left << setw(10) << book.getId() << setw(16) << book.getTitle() 
        << setw(16) << book.getAuthor() << setw(11) << book.getGenre() << setw(10) 
        << setprecision(2) << right << fixed << showpoint << book.getPages() << endl;
    return output;
}