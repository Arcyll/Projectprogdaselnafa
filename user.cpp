#include "user.h"
using namespace std;

Donasi::Donasi() {
    this->firstName = "";
    this->lastName = "";
}

Donasi::Donasi(string firstName, string lastName) {
    this->firstName = firstName;
    this->lastName = lastName;
}

string Donasi::getFirstName() {
    return firstName;
}

string Donasi::getLastName() {
    return lastName;
}

string Donasi::getFullName() {
    return firstName + " " + lastName;
}

void Donasi::setName(string firstName, string lastName) {
    this->firstName = firstName;
    this->lastName = lastName;
}

bool Donasi::isEmpty() {
    return (firstName.empty() || lastName.empty());
}
