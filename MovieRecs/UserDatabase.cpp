#include "UserDatabase.h"
#include "User.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

UserDatabase::UserDatabase() {}

bool UserDatabase::load(const string& filename)
{
    ifstream file(filename);
    if (!file)                // if failed to open file
    {
        cerr << "Error: Cannot open " << filename << "!" << endl;
        return false;
    }
    
    string name;
    string email;
    int nMovies;
    string movie;
    vector<string> history;
    
    while(getline(file, name))
    {
        getline(file, email);
        if(get_user_from_email(email) != nullptr) //user already exists
            return false;
        
        file >> nMovies;
        file.ignore(10000, '\n');       //skips the rest of line
        history.clear();
        for(int i=0; i<nMovies; i++)
        {
            getline(file, movie);
            history.push_back(movie);
        }
        
        User* user = new User(name, email, history);
        userDB.insert(email, user);
        
        file.ignore(10000, '\n');       //skips thelast line
    }
    
    return true;
}

User* UserDatabase::get_user_from_email(const string& email) const
{
    auto it = userDB.find(email);
    if(it.is_valid())                  //check if user exists
        return it.get_value();
    return nullptr;
}
