#include "Profile.h"
#include <fstream>
#include <iostream>
using namespace std;

//Profile::Profile(): name("Guest"), email("")  {}

Profile::Profile(const string& name, const string& email): name(name), email(email) {}

string Profile::GetName() const {return name;}

string Profile::GetEmail() const {return email;}

void Profile::SetName(const string& name) {this->name = name;}

void Profile::SetEmail(const string& email) {this->email = email;}

void Profile::DisplayProfile() const {
    cout << "Profile Information:" << endl;
    cout << "Name: " << name << endl;
    cout << "Email: " << email << endl;
}

void Profile::SaveProfile(const string& filename) const {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << name << endl;
        outFile << email << endl;
        outFile.close();
    } else {
        cout << "Error saving profile to file." << endl;
    }
}

void Profile::LoadProfile(const string& filename) {
    ifstream inFile(filename);
    if (inFile.is_open()) {
        getline(inFile, name);
        getline(inFile, email);
        inFile.close();
    } else {
        cout << "Error loading profile from file. Using default values." << endl;
    }
}
