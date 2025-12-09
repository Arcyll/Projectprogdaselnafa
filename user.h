#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class Donasi {
private:
    string firstName;
    string lastName;

public:
    // Constructor
    Donasi();
    Donasi(string firstName, string lastName);
    
    // Getters
    string getFirstName();
    string getLastName();
    string getFullName();
    
    // Setters
    void setName(string firstName, string lastName);
    
    // Check if donation data is filled
    bool isEmpty();
};

#endif
