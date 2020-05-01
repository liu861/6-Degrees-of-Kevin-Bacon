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
    for(auto& itr : mActorsToMoviesMap)
    {
        reverseMap(itr.first, mActorsToMoviesMap[itr.first]);
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
        //if movie is already in movies to actors map, add actorName to that movie's vector
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
    //use movies to actors map and create actor edge function
    //to populate the map
    //key(movie name) used to connect every other actor in the actor name vector
    //for every movie in actors map
    for(auto& i : mMoviesToActorsMap)
    {
        const std::string& movieName = i.first;
        //get actors that were in this movie
        //create vector of actors
        const std::vector<std::string>& actors = mMoviesToActorsMap[movieName];
        //make n^2 edges between the actors (because edges = nodes^2)
        for(int j = 0; j < actors.size(); j++)
        {
            //set first actor to pair
            ActorNode* firstActor = mGraph.getActorNode(actors[j]);
            for(int k = j+1; k < actors.size(); k++)
            {
                //set second actor to pair
                ActorNode* secondActor = mGraph.getActorNode(actors[k]);
                //use createActorEdge from IMDBGraph
                mGraph.createActorEdge(firstActor, secondActor, movieName);
            }
        }
    }
}

// Function: findRelationship
// Purpose: Tries to find a relationship between two actors, using a BFS
// and returns a string with the result of the search.
// Input: Name of two actors to check for a relationship
// Returns: A string with the search results
std::string IMDBData::findRelationship(const std::string& fromActor, const std::string& toActor)
{
    //string to return result of the search with
    std::string result = "";
    //first, make sure both actors are in the graph, if not, output error
    if(!mGraph.containsActor(fromActor) && !mGraph.containsActor(toActor))
    {
        result += fromActor;
        result += " is unknown!\n";
        result += toActor;
        result += " is unknown!\n";
        return result;
    }
    if(!mGraph.containsActor(fromActor))
    {
        result += fromActor;
        result += " is unknown!\n";
    }
    else if(!mGraph.containsActor(toActor))
    {
        result += toActor;
        result += " is unknown!\n";
    }
    else
    {
        //now implement BFS
        //create queue of actorNodes, and enqueue the node we're starting from
        ActorNode* begin = mGraph.getActorNode(fromActor);
        ActorNode* target = mGraph.getActorNode(toActor);
        
        //create queue
        std::queue<ActorNode*> BFSQueue;
        BFSQueue.push(begin);
        
        //boolean to keep track of whether path is found
        bool pathFound = false;
        ActorNode* currentNode = nullptr;
        //while the BFS queue is not empty
        while(BFSQueue.size() != 0)
        {
            //dequeue the front actor node, save in currentNode
            currentNode = BFSQueue.front();
            BFSQueue.pop();
            //if currentNode = target, we found a path!
            if(currentNode == target)
            {
                pathFound = true;
                break;
            }
            //otherwise if currentNode's visited bool is false
            else if(currentNode->mIsVisited == false)
            {
                //visit currentNode
                currentNode->mIsVisited = true;
                //iterate through currentNode's edges
                for(auto& i : currentNode->mEdges)
                {
                    //if the visited flag is false
                    if(i.mOtherActor->mIsVisited == false)
                    {
                        //if the adjacent node's path is empty
                        if(i.mOtherActor->mPath.size() == 0)
                        {
                            //set adjacent node's path to current actor's path
                            i.mOtherActor->mPath = currentNode->mPath;
                            //push adjacent node's relevant information (movie and actor name)
                            //append additional pathpair to represent hop of visiting
                            PathPair info(i.mMovieName, i.mOtherActor->mName);
                            i.mOtherActor->mPath.push_back(info);
                        }
                        //enqueue the adjacent node
                        BFSQueue.push(i.mOtherActor);
                    }
                }
            }
        }
        //The BFS should finish in one of two cases:
        //1. The queue becomes empty (in which case it failed to find a path)
        //2. The second actor was found (it found a path)
        //so if the path was found
        if(pathFound)
        {
            result += "Found a path! (";
            result += std::to_string(target->mPath.size());
            result += " hops)\n";
            //display path
            int traverse = 1; //counter through path
            std::string startActor = fromActor;
            result += startActor;
            result += " was in...\n";
            for(auto& i : currentNode->mPath)
            {
                std::string movie = i.getMovieName();
                result += movie;
                result += " with ";
                std::string nextActor = i.getActorName();
                result += nextActor;
                if(currentNode->mPath.size() == traverse)
                {
                    result += "\n";
                }
                else
                {
                    result += " who was in...\n";
                }
                traverse++;
            }
        }
        //otherwise, just output that the path was not found
        else
        {
            result = "Didn't find a path\n";
        }
    }
    mGraph.clearVisited();
    return result;
}


// Leave here! Do not edit!!!
// DO NOT REMOVE THIS LINE
std::vector<std::string> IMDBData::sEmptyVector;
