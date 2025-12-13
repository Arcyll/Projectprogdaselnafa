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
    Book(int id, string title, string author, int year, string donaturFirstName, string donaturLastName);
    
    int getId();
    string getTitle();
    string getAuthor();
    int getYear();
    string getDonaturFirstName();
    string getDonaturLastName();
    string getDonaturFullName();
    bool getIsDonated();
    string getDonatedTo();
    
    void setDonated(string recipient);
    
    void display();
    void displayDonated();
};

#endif
