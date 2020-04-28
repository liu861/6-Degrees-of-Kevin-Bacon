#include "IMDBData.h"
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>

// Function: Default Constructor
// Purpose: Loads in the actor/movie file specified,
// and populates the data into the appropriate hash maps.
// Also constructs the graph with actor relationships.
// Input: Name of file to load (by reference)
// Returns: Nothing
IMDBData::IMDBData(const std::string& fileName)
{
    //open file
    std::ifstream ifile(fileName);
    //if file couldn't be opened
    if(!ifile.is_open())
    {
        std::cout << "Error: File " << fileName << " was not found" << std::endl;
    }
    //otherwise open and iterate through file!
    else
    {
        //string to store actor name
        std::string actor = "";
        //vector to store movie names
        std::vector<std::string> movies;
        //string use getline with to store lines from file
        std::string line;
        //iterate through file
        while(!ifile.eof())
        {
            line.clear();
            //get a line
            std::getline(ifile, line);
            //if line is an actor(first line)
            if(line[0] != '|')
            {
                //if first actor
                if(actor == "")
                {
                    //update prev actor
                    actor = line;
                    //clear movies
                    movies.clear();
                }
                //otherwise we have a prev actor to push
                else
                {
                    //push prev actor into map
                    mActorsToMoviesMap[actor] = movies;
                    //update prev actor
                    actor = line;
                    movies.clear();
                }
            }
            //otherwise the line is a movie
            else
            {
               //push movies into movies vector
               std::string movie = line.substr(1);
               movies.push_back(movie);
            }
        }
        //close file
        ifile.close();
    }
    
    //generate movie to actors map
    for(auto itr : mActorsToMoviesMap)
    {
        reverseMap(itr.first, itr.second);
    }
}

// Function: reverseMap
// Purpose: This is a helper function that is used to generate
// the reverse map (movies to actors)
// Input: Name of actor (by reference), vector of their movies (by reference)
// Returns: Nothing
void IMDBData::reverseMap(const std::string& actorName, const std::vector<std::string>& movies)
{
    for(int i = 0; i < movies.size(); i++)
    {
        //if movie is already in map, add actorName to that movie's vector
        if(mMoviesToActorsMap.find(movies[i]) != mMoviesToActorsMap.end())
        {
            mMoviesToActorsMap[movies[i]].push_back(actorName);
        }
        //otherwise, create a new vector of actorNames for the movie with
        //that actor's name in it (for now)
        else
        {
            std::vector<std::string> temp;
            temp.push_back(actorName);
            mMoviesToActorsMap[movies[i]] = temp;
        }
    }
            
}

// Function: getMoviesFromActor
// Purpose: Given an actor's name, returns a vector containing their movies
// Input: Name of actor (by reference)
// Returns: Vector of movies (by reference)
const std::vector<std::string>& IMDBData::getMoviesFromActor(const std::string& actorName)
{
	// TODO: Implement
    //if the actors to movies map contains the actorName, return the lookup of the map
    if(mActorsToMoviesMap.find(actorName) != mActorsToMoviesMap.end())
    {
        return mActorsToMoviesMap[actorName];
    }
    //otherwise, return sEmptyVector
    return sEmptyVector;
}

// Function: getActorsFromMovie
// Purpose: Given a movie's name, returns the name of its actors
// Input: Name of movie (by reference)
// Returns: Vector of actors (by reference)
const std::vector<std::string>& IMDBData::getActorsFromMovie(const std::string& movieName)
{
	// TODO: Implement
    //if movieName is found in movies to actors map, return the lookup
    if(mMoviesToActorsMap.find(movieName) != mMoviesToActorsMap.end())
    {
        return mMoviesToActorsMap[movieName];
    }
    //otherwise, return sEmptyVector
    return sEmptyVector;
}

// Function: createGraph
// Purpose: This helper function constructs the IMDBGraph from the movie to actors map
// For each movie, it connects every actor in the film with the other actors in the film
// Input: None
// Returns: Nothing
void IMDBData::createGraph()
{
	// TODO: Implement
}

// Function: findRelationship
// Purpose: Tries to find a relationship between two actors, using a BFS
// and returns a string with the result of the search.
// Input: Name of two actors to check for a relationship
// Returns: A string with the search results
std::string IMDBData::findRelationship(const std::string& fromActor, const std::string& toActor)
{
	// TODO: Implement
	return "";
}


// Leave here! Do not edit!!!
// DO NOT REMOVE THIS LINE
std::vector<std::string> IMDBData::sEmptyVector;
