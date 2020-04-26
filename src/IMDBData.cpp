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
	// TODO: Implement
    //open file
    std::ifstream ifile(fileName);
    if(ifile.is_open())
    {
        //string to store actor name
        std::string actor = "";
        //vector to store movie names
        std::vector<std::string> movies;
        //string to getlines from
        std::string line;
        //iterate through file
        while(!ifile.eof())
        {
            //get a line
            std::getline(ifile, line);
            //if line is an actor
            if(line[0] != '|')
            {
                //if actor DNE
                if(actor == "")
                {
                    actor = line;
                    movies.clear();
                }
                else
                {
                    //push actor into map
                    mActorsToMoviesMap[actor] = movies;
                    actor = line;
                    movies.clear();
                }
            }
            //line is a movie!
            else
            {
                //push movies into movies vector
                std::string movie = line.substr(1);
                movies.push_back(movie);
            }
        }
        ifile.close();
    }
    //if file could not be opened
    else
    {
        std::cout << "Error: File " << fileName << " was not found" << std::endl;
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
	// TODO: Implement
}

// Function: getMoviesFromActor
// Purpose: Given an actor's name, returns a vector containing their movies
// Input: Name of actor (by reference)
// Returns: Vector of movies (by reference)
const std::vector<std::string>& IMDBData::getMoviesFromActor(const std::string& actorName)
{
	// TODO: Implement
	return sEmptyVector;
}

// Function: getActorsFromMovie
// Purpose: Given a movie's name, returns the name of its actors
// Input: Name of movie (by reference)
// Returns: Vector of actors (by reference)
const std::vector<std::string>& IMDBData::getActorsFromMovie(const std::string& movieName)
{
	// TODO: Implement
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
