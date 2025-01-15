#include "Profile.h"
#include <iostream>
using namespace std;

// Constructor
Profile::Profile(const string& name, const string& email)
    : name(name), email(email) {}

// Getters
string Profile::GetName() const {
    return name;
}

string Profile::GetEmail() const {
    return email;
}

// Setters
void Profile::SetName(const string& name) {
    this->name = name;
}

void Profile::SetEmail(const string& email) {
    this->email = email;
}

// Display Profile Information
void Profile::DisplayProfile() const {
    cout << "Profile Information:" << endl;
    cout << "Name: " << name << endl;
    cout << "Email: " << email << endl;
}
