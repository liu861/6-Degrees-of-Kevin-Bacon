#include <iostream>
#include <string>
#include <chrono>

#include "IMDBData.h"

// Option 1
// Function: moviesFromActor
// Purpose: Uses CIN and COUT to get an actor name from the user and 
// display the actor and the movies they've been in If the actor isn't in the map, 
// it will display that the actor is unknown
// Input: A populated IMDB data graph
// Side effects: Uses CIN and COUT to interact with the user.
// Returns: Nothing
void moviesFromActor(IMDBData& data)
{
	// TODO: Implement
}

// Option 2
// Function: actorFromMovies
// Purpose: Uses CIN and COUT to get a movie name from the user and 
// display the movie and the actors they've been in If the movie isn't in the map, 
// it will display that the movie is unknown
// Input: A populated IMDB data graph
// Side effects: Uses CIN and COUT to interact with the user.
// Returns: Nothing
void actorFromMovies(IMDBData& data)
{
	// TODO: Implement
}

// Option 3
// Function: relationship
// Purpose: Uses CIN and COUT to get 2 actor names
// Using the string returned from findRelationship displays the
// movies linking the 2 actors
// Input: A populated IMDB data graph
// Side effects: Uses CIN and COUT to interact with the user.
// Returns: Nothing
void relationship(IMDBData& data)
{
	// TODO: Implement
}


int main(int argc, char** argv)
{
	std::cout << "Enter an actor file to load: " << std::endl;
	std::cout << "> ";
	std::string fname;
	std::getline(std::cin, fname);

	// Time out how long it takes to load the data
	std::cout << "Loading..." << std::endl;

	auto start = std::chrono::high_resolution_clock::now();

	IMDBData data(fname);

	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
	float seconds = duration / 1000000000.0f;

	std::cout << "Took " << seconds << "s\n";

	// Time out how long it takes to create the graph
	std::cout << "Creating graph..." << std::endl;

	start = std::chrono::high_resolution_clock::now();

	data.createGraph();

	end = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
	seconds = duration / 1000000000.0f;

	std::cout << "Took " << seconds << "s\n";

	while (true)
	{
		std::cout << std::endl;
		std::cout << "Main Menu" << std::endl;
		std::cout << "1. Get movies from actor" << std::endl;
		std::cout << "2. Get actors from movies" << std::endl;
		std::cout << "3. Find relationship between actors" << std::endl;
		std::cout << "4. Quit" << std::endl;
		std::cout << "> ";

		std::string option;
		std::getline(std::cin, option);

		if (option == "1")
		{
			moviesFromActor(data);
		}
		else if (option == "2")
		{
			actorFromMovies(data);
		}
		else if (option == "3")
		{
			relationship(data);
		}
		else if (option == "4")
		{
			std::cout << "Goodbye!" << std::endl;
			break;
		}
		else
		{
			std::cout << "Invalid option, please try again." << std::endl;
		}
	}

	return 0;

}