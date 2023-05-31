// ProyectoFinal.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include "Biblioteca.h"
#include <iostream>

int main() 
{
    //std::cout << sizeof(ClientData);
    ofstream OutLibrary{ "Library.dat", ios::out | ios::binary };

    // exit program if ofstream could not open file
    if (!OutLibrary) {
        cerr << "File could not be opened." << endl;
        exit(EXIT_FAILURE);
    }

       Libro blankbook; // constructor zeros out each data member

    // output 100 blank records to file
    for (int i{ 0 }; i < 100; ++i) {
        OutLibrary.write(
            reinterpret_cast<const char*>(&blankbook), sizeof(Libro));
    }

    // open file for reading and writing                                  
    fstream inOutLibrary{ "Library.dat", ios::in | ios::out | ios::binary };

    // exit program if fstream cannot open file
    if (!inOutLibrary) {
        cerr << "File could not be opened." << endl;
        exit(EXIT_FAILURE);
    }


    cout << "Enter book number (1 to 100, 0 to end input)\n? ";

    int Id;
    string title;
    string author;
    int year;
    string genre;
    int pages;
    int quantity;
    int available;
    int borrowed;
    int reserved;

    cin >> Id; // read book number

    // user enters information, which is copied into file
    while (Id > 0 && Id <= 100) 
    {
        // user does the entries for the book
        system("cls");
        cout << "Enter title, author, year, genre, pages, quantity, available, borrowed, reserved\n? ";
        cin >> title;
        cin >> author;
        cin >> year;
        cin >> genre;
        cin >> pages;
        cin >> quantity;
        cin >> available;
        cin >> borrowed;
        cin >> reserved;

        // create ClientData object
        Libro book{Id, title, author, year, genre, pages, quantity, available, borrowed, reserved};

        // seek position in file of user-specified record
        inOutLibrary.seekp((book.getId() - 1) * sizeof(Libro));

        // write user-specified information in file                  
        inOutLibrary.write(reinterpret_cast<const char*>(&book), sizeof(Libro));

        // enable user to enter another account
        cout << "Enter book number\n? ";
        cin >> Id;
        cin.ignore();
    }

    // output column heads
    cout << left << setw(10) << "Id" << setw(16) << "Title" << setw(11)
		<< "Author" << setw(10) << "Year" << setw(10)
        << "Genre" << setw(10) << "Pages" << setw(10) 
        << "Quantity" << setw(10) << "Available" << setw(10)
        << "Borrowed" << setw(10) << "Reserved" << endl;   

    Libro book; // create record

    // read first record from file                       
    inOutLibrary.read(reinterpret_cast<char*>(&book), sizeof(Libro));

    // read all records from file          
    while (inOutLibrary) {
        // display record
        if (book.getId() != 0) {
            cout << book;
        }

        // read next from file                               
        inOutLibrary.read(reinterpret_cast<char*>(&book), sizeof(inOutLibrary));
    }

    Choice choice; // store user choice

    // enable user to specify action
    while ((choice = enterChoice()) != Choice::END) {
        switch (choice) {
        case Choice::PRINT: // create text file from record file
            createTextFile(inOutLibrary);
            break;
        case Choice::UPDATE: // update record
            updateRecord(inOutLibrary);
            break;
        case Choice::NEW: // create record
            newRecord(inOutLibrary);
            break;
        case Choice::DELETE: // delete existing record
            deleteRecord(inOutLibrary);
            break;
        default: // display error if user does not select valid choice
            cerr << "Incorrect choice" << endl;
            break;
        }

        inOutLibrary.clear(); // reset end-of-file indicator
    }
}