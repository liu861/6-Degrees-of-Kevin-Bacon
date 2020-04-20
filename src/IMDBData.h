#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "IMDBGraph.h"

class IMDBData
{
public:
	// Function: Default Constructor
	// Purpose: Loads in the actor/movie file specified,
	// and populates the data into the appropriate hash maps.
	// Also constructs the graph with actor relationships.
	// Input: Name of file to load (by reference)
	// Returns: Nothing
	IMDBData(const std::string& fileName);

	// Function: reverseMap
	// Purpose: This is a helper function that is used to generate
	// the reverse map (movies to actors)
	// Input: Name of actor (by reference), vector of their movies (by reference)
	// Returns: Nothing
	void reverseMap(const std::string& actorName, const std::vector<std::string>& movies);

	// Function: getMoviesFromActor
	// Purpose: Given an actor's name, returns a vector containing their movies
	// Input: Name of actor (by reference)
	// Returns: Vector of movies (by reference)
	const std::vector<std::string>& getMoviesFromActor(const std::string& actorName);

	// Function: getActorsFromMovie
	// Purpose: Given a movie's name, returns the name of its actors
	// Input: Name of movie (by reference)
	// Returns: Vector of actors (by reference)
	const std::vector<std::string>& getActorsFromMovie(const std::string& movieName);

	// Function: createGraph
	// Purpose: This helper function constructs the IMDBGraph from the movie to actors map
	// For each movie, it connects every actor in the film with the other actors in the film
	// Input: None
	// Returns: Nothing
	void createGraph();

	// Function: findRelationship
	// Purpose: Tries to find a relationship between two actors, using a BFS
	// and returns a string with the result of the search.
	// Input: Name of two actors to check for a relationship
	// Returns: A string with the search results
	std::string findRelationship(const std::string& fromActor, const std::string& toActor);
private:
	// Hash map which associates an actor with a vector of movies
	std::unordered_map<std::string, std::vector<std::string>> mActorsToMoviesMap;

	// Hash map which associates a movie with a vector of actors
	std::unordered_map<std::string, std::vector<std::string>> mMoviesToActorsMap;
	
	// Graph that shows relationships between actors (use for part 2)
	IMDBGraph mGraph;

	// Static helper variable used to have an empty vector (use for part 1)
	static std::vector<std::string> sEmptyVector;

};
