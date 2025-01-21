#ifndef PROFILE_H
#define PROFILE_H

#include <string>
using namespace std;

class Profile {
public:
    //Profile();
    Profile(const string& name = "Guest", const string& email = "");

    string GetName() const;
    string GetEmail() const;

    void SetName(const string& name);
    void SetEmail(const string& email);

    void DisplayProfile() const;
    void SaveProfile(const string& filename) const;
    void LoadProfile(const string& filename);

private:
    string name;
    string email;
};

#endif // PROFILE_H
