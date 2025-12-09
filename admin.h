#ifndef ADMIN_H
#define ADMIN_H

#include <string>
using namespace std;

class Admin {
private:
    string username;
    string password;

public:
    // Constructor
    Admin(string username, string password);
    
    // Authentication
    bool authenticate(string user, string pass);
    
    // Display menu
    void displayMenu();
};

#endif
