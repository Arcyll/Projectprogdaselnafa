#include "book.h"
#include <iostream>
#include <iomanip>
using namespace std;

Book::Book(int id, string title, string author, int year, string donaturFirstName, string donaturLastName) {
    this->id = id;
    this->title = title;
    this->author = author;
    this->year = year;
    this->donaturFirstName = donaturFirstName;
    this->donaturLastName = donaturLastName;
    this->isDonated = false;
    this->donatedTo = "-";
}

int Book::getId() {
    return id;
}

string Book::getTitle() {
    return title;
}

string Book::getAuthor() {
    return author;
}

int Book::getYear() {
    return year;
}

string Book::getDonaturFirstName() {
    return donaturFirstName;
}

string Book::getDonaturLastName() {
    return donaturLastName;
}

string Book::getDonaturFullName() {
    return donaturFirstName + " " + donaturLastName;
}

bool Book::getIsDonated() {
    return isDonated;
}

string Book::getDonatedTo() {
    return donatedTo;
}

void Book::setDonated(string recipient) {
    this->isDonated = true;
    this->donatedTo = recipient;
}

void Book::display() {
    cout << "  | " << setw(4) << id 
         << " | " << setw(30) << left << title 
         << " | " << setw(20) << author 
         << " | " << setw(6) << year
         << " | " << setw(25) << getDonaturFullName() << " |" << endl;
}

void Book::displayDonated() {
    cout << "  | " << setw(4) << id 
         << " | " << setw(30) << left << title 
         << " | " << setw(20) << author 
         << " | " << setw(25) << getDonaturFullName()
         << " | " << setw(20) << donatedTo << " |" << endl;
}
