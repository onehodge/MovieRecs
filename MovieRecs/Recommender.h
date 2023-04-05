#ifndef RECOMMENDER_INCLUDED
#define RECOMMENDER_INCLUDED

#include <string>
#include <vector>
#include <map>

class UserDatabase;
class MovieDatabase;
class Movie;

struct MovieAndRank
{
    MovieAndRank(const std::string& id, int score)
     : movie_id(id), compatibility_score(score)
    {}

    std::string movie_id;
    int compatibility_score;
};

class Recommender
{
  public:
    Recommender(const UserDatabase& user_database,
                const MovieDatabase& movie_database);
    std::vector<MovieAndRank> recommend_movies(const std::string& user_email,
                                               int movie_count);

  private:
    
    struct MovieRefAndRank        //created to implement tie breaker easier; instead of calling get_movie_from_ID and search, just use movie_ref
    {
        MovieRefAndRank(Movie* movie, int score)
         : movie_ref(movie), compatibility_score(score){}

        Movie* movie_ref;
        int compatibility_score;
    };
    
    const UserDatabase* udb;
    const MovieDatabase* mdb;
    static bool compareScores(const MovieRefAndRank& lhs, const MovieRefAndRank& rhs);
    
};

#endif // RECOMMENDER_INCLUDED
