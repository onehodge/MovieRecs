#ifndef USER_INCLUDED
#define USER_INCLUDED

#include <string>
#include <vector>

class User
{
  public:
    User(const std::string& full_name, const std::string& email,
         const std::vector<std::string>& watch_history):
        m_name(full_name), m_email(email), m_movies(watch_history) {}
    
    std::string get_full_name() const   {return m_name;}
    std::string get_email() const       {return m_email;}
    std::vector<std::string> get_watch_history() const  {return m_movies;}

  private:
    std::string m_name;
    std::string m_email;
    std::vector<std::string> m_movies;
};

#endif // USER_INCLUDED
