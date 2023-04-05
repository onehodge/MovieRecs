#include "Recommender.h"
#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "User.h"
#include "Movie.h"
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

Recommender::Recommender(const UserDatabase& user_database,
                         const MovieDatabase& movie_database)
{
    udb = &user_database;
    mdb = &movie_database;
}

bool Recommender::compareScores(const MovieRefAndRank& lhs, const MovieRefAndRank& rhs)
{
    //compare compatibility score first
    if (lhs.compatibility_score > rhs.compatibility_score)
        return true;
    if (lhs.compatibility_score < rhs.compatibility_score)
        return false;
    //tie breaker: movie rating
    if (lhs.movie_ref->get_rating() > rhs.movie_ref->get_rating())
        return true;
    if (lhs.movie_ref->get_rating() < rhs.movie_ref->get_rating())
        return false;
    //rank alphabetically
    return lhs.movie_ref->get_title() < rhs.movie_ref->get_title();
}

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count)
{
    map<Movie*, int> movie_scores;      //most efficient structure: retrieving score is O(1)
    User* u = udb->get_user_from_email(user_email);
    vector<string> history = u->get_watch_history();
    for(int i=0;i<history.size();i++)
    {
        Movie* m = mdb->get_movie_from_id(history[i]);  //for each movie in the watch history
        
        vector<string> directors = m->get_directors();
        vector<string> actors = m->get_actors();
        vector<string> genres = m->get_genres();

        for(int j=0;j<directors.size();j++)     //each director
        {
            vector<Movie*> m_list = mdb->get_movies_with_director(directors[j]);
            for(int k=0;k<m_list.size();k++)
                movie_scores[m_list[k]]+=20;    //movies with the director gets +20
        }
        for(int j=0;j<actors.size();j++)        //each actor
        {
            vector<Movie*> m_list = mdb->get_movies_with_actor(actors[j]);
            for(int k=0;k<m_list.size();k++)
                movie_scores[m_list[k]]+=30;    //movies with the director gets +30
        }
        for(int j=0;j<genres.size();j++)        //each genre
        {
            vector<Movie*> m_list = mdb->get_movies_with_genre(genres[j]);
            for(int k=0;k<m_list.size();k++)
                movie_scores[m_list[k]]+=1;     //movies with the genre gets +1
        }
    }//finished score calculation
    
    vector<MovieRefAndRank> recs1;
    for(auto it : movie_scores)                 //iterate through movies in the map
    {
        if(find(history.begin(), history.end(), it.first->get_id()) != history.end())
            continue;               //do not add movies already watched
        recs1.push_back(MovieRefAndRank(it.first,it.second));
    }
    
    //rank the movies using STL sort and our own compare bool function
    sort(recs1.begin(), recs1.end(), compareScores);
    
    vector<MovieAndRank> recs;
    for(int i=0;i<recs1.size();i++)     //convert to MovieAndRank format
    {
        if(i>=movie_count) break;   //stop adding if reached movie_count
        string id = recs1[i].movie_ref->get_id();
        int score = recs1[i].compatibility_score;
        recs.push_back(MovieAndRank(id, score));
    }
    return recs;
}

