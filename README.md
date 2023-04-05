# MovieRecs

a movie recommender based on a user's watch history and the given movie database.

This project aims to develop an app that provides movie recommendations among 20K movies to up to 100K users, based on their individual watching history and the attributes of movies. The database can be found in the Data folder. In users.txt each user has a history of movies they've watched (up to hundreds of movies); in movies.txt each movie has a set of attributes that describe it, including the movie title, release year, director(s), actor(s), genre(s), and a movie rating (e.g., 3.5 stars).

To identify recommended movies for a given person P, the app calculates a compatibility score and ranks all movies. The algorithm is as followed:
- Use the provided email address to find the user's watch history, scan through each movie M
- For each director D associated with M, each movie in the movie database that has D in its list of directors gets +20 compatibility score
- For each actor A associated with M, each movie in the movie database that has A in its list of actors gets +30 compatibility score
- For each genre G associated with M, each movie in the movie database that has G in its list of genres gets +1 compatibility score
- Tie-breaker: movie ratings

Below is a sample input-output: 
```
Enter a user's email for recommendations: KabiL@aol.com
Enter number of recommendations to provide: 8

User Kabir Luna has watched the following movies:
Notes On Blindness
Lana: Queen of the Amazons
The Big Bang
Homefront
For Ellen
Hitch
... the rest of the movies are omitted for this example
The Valley of Gwangi

Here are the recommendations:

1. The Blues Brothers (1980)
   Rating: 3.79643
   Compatibility Score: 390

2. The Player (1992)
   Rating: 3.92309
   Compatibility Score: 281

3. Trust the Man (2005)
   Rating: 2.82645
   Compatibility Score: 250

4. Never So Few (1959)
   Rating: 3.11111
   Compatibility Score: 234

5. Knocked Up (2007)
   Rating: 3.40438
   Compatibility Score: 230

6. The Ghost Comes Home (1940)
   Rating: 2
   Compatibility Score: 230

7. Hot Fuzz (2007)
   Rating: 3.86654
   Compatibility Score: 227

8. Filth (2013)
   Rating: 3.64121
   Compatibility Score: 221
```
