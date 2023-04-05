#include "MovieDatabase.h"
#include "Movie.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

MovieDatabase::MovieDatabase() {}

bool MovieDatabase::load(const string& filename)
{
    ifstream file(filename);
    if (!file)                // if failed to open file
    {
        cerr << "Error: Cannot open " << filename << "!" << endl;
        return false;
    }
    
    string id,title,year;
    float rating;
    
    while(getline(file, id))
    {
        getline(file, title);
        getline(file, year);
        
        string s;
        getline(file, s);
        vector<string> directors = chop(s);
        getline(file, s);
        vector<string> actors = chop(s);
        getline(file, s);
        vector<string> genres = chop(s);
        
        file >> rating;
        file.ignore(10000, '\n');       //skips rest of the line
        
        Movie* movie = new Movie(id, title, year, directors, actors, genres, rating);
        movieDB.insert(id, movie);              //insert into the BST
        
        for(int i=0;i<directors.size();i++)     //create other BST too
            directorsDB.insert(directors[i], movie);
        for(int i=0;i<actors.size();i++)
            actorsDB.insert(actors[i], movie);
        for(int i=0;i<genres.size();i++)
            genresDB.insert(genres[i], movie);
        
        file.ignore(10000, '\n');       //skips the last line
    }
    return true;
}

vector<string> MovieDatabase::chop(const std::string& s)
{
    vector<string> db;
    string cur_name="";
    for(int i=0;i<s.length();i++)
    {
        if(s[i]==',')
        {
            db.push_back(cur_name);
            cur_name = "";
        }
        else
            cur_name += s[i];
    }
    db.push_back(cur_name);
    return db;
}

Movie* MovieDatabase::get_movie_from_id(const string& id) const
{
    auto it = movieDB.find(id);
    if(it.is_valid())                   //check if movie exists
        return it.get_value();
    return nullptr;
}

vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const
{
    vector<Movie*> db;
    auto it = directorsDB.find(director);
    while(it.is_valid())
    {
        db.push_back(it.get_value());
        it.advance();
    }
    return db;
}

vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const
{
    vector<Movie*> db;
    auto it = actorsDB.find(actor);
    while(it.is_valid())
    {
        db.push_back(it.get_value());
        it.advance();
    }
    return db;
}

vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const
{
    vector<Movie*> db;
    auto it = genresDB.find(genre);
    while(it.is_valid())
    {
        db.push_back(it.get_value());
        it.advance();
    }
    return db;
}
