#ifndef BOOK_H
#define BOOK_H

#include <string>
using namespace std;

class Book {
private:
    int id;
    string title;
    string author;
    int year;
    string donaturFirstName;
    string donaturLastName;
    bool isDonated;
    string donatedTo;

public:
    // Constructor
    Book(int id, string title, string author, int year, string donaturFirstName, string donaturLastName);
    
    // Getters
    int getId();
    string getTitle();
    string getAuthor();
    int getYear();
    string getDonaturFirstName();
    string getDonaturLastName();
    string getDonaturFullName();
    bool getIsDonated();
    string getDonatedTo();
    
    // Setters
    void setDonated(string recipient);
    
    // Display
    void display();
    void displayDonated();
};

#endif
