#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

#ifndef PROFILE_H
#define PROFILE_H


class Profile {
private:
    string name;       // User's name
    string email;      // User's email

public:
    // Constructor
    Profile(const string& name = "Guest", const string& email = "");

    // Getters
    string GetName() const;
    string GetEmail() const;

    // Setters
    void SetName(const string& name);
    void SetEmail(const string& email);

    // Display Profile Information
    void DisplayProfile() const;
};

#endif // PROFILE_H
