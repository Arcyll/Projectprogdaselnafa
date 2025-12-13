#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class Donasi {
private:
    string firstName;
    string lastName;

public:
    Donasi();
    Donasi(string firstName, string lastName);
    
    string getFirstName();
    string getLastName();
    string getFullName();
    
    void setName(string firstName, string lastName);
    
    // cek jumlah donasi
    bool isEmpty();
};

#endif
