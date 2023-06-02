// ProyectoFinal.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include "Biblioteca.h"
#include <iostream>
#include<sys/stat.h>

int main() 
{
    ofstream outLibrary{ "Library.csv", ios::out | ios::binary };
    if (!outLibrary)
    {
		cerr << "File could not be opened." << endl;
		exit(EXIT_FAILURE);
	}   
    Libro blankbook;

   for (int i{ 0 }; i < 100; ++i)
    {
        outLibrary.write(
		    reinterpret_cast<const char*>(&blankbook), sizeof(Libro));
	}
    outLibrary.close();
    // open file for reading and writing                                  
    fstream inOutLibrary{ "Library.csv", ios::in | ios::out | ios::binary};

    // exit program if fstream cannot open file
    if (!inOutLibrary) 
    {
        cerr << "File could not be opened." << endl;
        exit(EXIT_FAILURE);
    }

    Choice choice; // store user choice

    // enable user to specify action
    system("cls");
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
        case Choice::SEARCH:
            searchBook(inOutLibrary);
            break;
        default: // display error if user does not select valid choice
            cerr << "Incorrect choice" << endl;
            break;
        }

        inOutLibrary.clear(); // reset end-of-file indicator
    }
}