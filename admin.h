#ifndef ADMIN_H
#define ADMIN_H

#include <string>
using namespace std;

class Admin {
private:
    string username;
    string password;

public:
    Admin(string username, string password);
    
    bool authenticate(string user, string pass);
    
    void displayMenu();
};

#endif
