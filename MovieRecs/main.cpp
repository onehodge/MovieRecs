#include "UserDatabase.h"
#include "User.h"
#include "MovieDatabase.h"
#include "Movie.h"
#include "Recommender.h"
#include <iostream>
#include <string>
using namespace std;

//////////////////////////i/////////////////////////////////////////////////////
//
// You are free to do whatever you want with this file, since you won't
// be turning it in.  Presumably, you will make changes to help you test
// your classes.  For example, you might try to implement only some User
// member functions to start out with, and so replace our main routine with
// one that simply creates a User and verifies that the member functions you
// implemented work correctly.
//
//////////////////////////i/////////////////////////////////////////////////////


  // If your program is having trouble finding these files. replace the
  // string literals with full path names to the files.  Also, for test
  // purposes, you may want to create some small, simple user and movie
  // data files to makde debuggiing easier, so you can replace the string
  // literals with the names of those smaller files.

const string USER_DATAFILE  = "/Users/onehodge/Desktop/MovieRecs/Data/users.txt";
const string MOVIE_DATAFILE = "/Users/onehodge/Desktop/MovieRecs/Data/movies.txt";


int main()
{
	UserDatabase udb;
    MovieDatabase mdb;
	if (!udb.load(USER_DATAFILE))
	{
		cout << "Failed to load user data file " << USER_DATAFILE << "!" << endl;
		return 1;
	}
    if (!mdb.load(MOVIE_DATAFILE))
    {
        cout << "Failed to load user data file " << MOVIE_DATAFILE << "!" << endl;
        return 1;
    }
    Recommender netflix(udb,mdb);
    for (;;)
    {
        cout << "Enter user email address (or quit): ";
        string email;
        getline(cin, email);
        if (email == "quit")
            return 0;
        User* u = udb.get_user_from_email(email);
        if (u == nullptr)
            cout << "No user in the database has that email address." << endl;
        else
        {
            cout << "Found " << u->get_full_name() << endl;
            cout << "Enter number of recommendations to provide: ";
            int n; cin>>n;
            cout << "User "<< u->get_full_name() <<" has watched the following movies:\n";
            vector<string> history = u->get_watch_history();
            for(int i=0;i<history.size();i++)
                cout<<mdb.get_movie_from_id(history[i])->get_title()<<endl;
            cout << "\nBelow are the recommendations:\n";
            vector<MovieAndRank> results = netflix.recommend_movies(email, n);
            for (int i = 0; i < results.size(); i++)
            {
                const MovieAndRank& mr = results[i];
                Movie* m = mdb.get_movie_from_id(mr.movie_id);
                cout << i+1 << ". " << m->get_title() << " (" << m->get_release_year() << ")\n Rating: "<< m->get_rating() << "\n Compatibility Score: " << mr.compatibility_score << "\n\n";
            }
        }
    }
    
    
    
    /*
    for (;;)
    {
        cout << "Enter actor name (or quit): ";
        string actor;
        getline(cin, actor);
        if (actor == "quit")
            return 0;
        vector<Movie*> m = mdb.get_movies_with_actor(actor);
        if (m.size() == 0)
            cout << "No movie in the database with that actor." << endl;
        else
        {
            for(int i=0;i<m.size();i++)
                cout<<m[i]->get_title()<<endl;
            cout<<m.size()<<" movies found."<<endl;
        }
    }
    */

    
    /*
    for (;;)
    {
        cout << "Enter movie ID (or quit): ";
        string id;
        getline(cin, id);
        if (id == "quit")
            return 0;
        Movie* m = mdb.get_movie_from_id(id);
        if (m == nullptr)
            cout << "No movie in the database has that id." << endl;
        else
        {
            cout << "Found " << m->get_title() << ", rating " << m->get_rating()<< endl;
            vector<string> actors = m->get_actors();
            cout << "List of actors: "<<endl;
            for(int i=0;i<actors.size();i++)
                cout<<actors[i]<<" + ";
            cout<<endl;
        }
    }
     */
    
    /*
	for (;;)
	{
		cout << "Enter user email address (or quit): ";
		string email;
		getline(cin, email);
		if (email == "quit")
			return 0;
		User* u = udb.get_user_from_email(email);
		if (u == nullptr)
			cout << "No user in the database has that email address." << endl;
		else
			cout << "Found " << u->get_full_name() << endl;
	}
     */
    
}
