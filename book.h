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
    string donorFirstName;
    string donorLastName;
    bool isDonated;
    string donatedTo;

public:
    // Constructor
    Book(int id, string title, string author, int year, string donorFirstName, string donorLastName);
    
    // Getters
    int getId();
    string getTitle();
    string getAuthor();
    int getYear();
    string getDonorFirstName();
    string getDonorLastName();
    string getDonorFullName();
    bool getIsDonated();
    string getDonatedTo();
    
    // Setters
    void setDonated(string recipient);
    
    // Display
    void display();
    void displayDonated();
};

#endif
