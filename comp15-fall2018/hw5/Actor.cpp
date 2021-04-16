/*
 * Filename: Graph.cpp
 * Contains: Implementation of the template Graph class 
 * Part of: Homework 5 assignment "Graph Traversal" for Comp 15 Fall 2018
 *
 */

#include <iostream>
#include <ostream>
#include <string>
#include "Actor.h"
#include "LinkedList.h"
using namespace std;

// Function: constructor
// Parameters: none
// Returns: nothing
// Does: default constructor
Actor::Actor()
{
   name = "";
   movies.make_empty();
}

// Function: parameterized constructor
// Parameters: integer (size of graph)
// Returns: nothing
// Does: parametrized constructor
Actor::Actor(string n)
{
    name = n;
    //for(int i = 0; i < m->size(); i++)
    //    movies.insert(m[i]);
}

// Function: insertMovie
// Input: String
// Returns: Nothing
// Does: inserts movie into a linked list of that actor's movies
void Actor::insertMovie(string movie)
{
    movies.insert(movie);
    return;
}

// Function: inMovie
// Input: String
// Returns: bool value
// Does: returns true if Actor was in movie(in LL), otherwise false
bool Actor::inMovie(string movie)
{
    int index = 0;
    while(index < movies.get_length())
    {
        if(movies.get_value_at(index).compare(movie) == 0)
            return true;

        index++;
    }
    return false;
}

// Function: connect
// Input: Actor
// Returns: string
// Does: returns name of movie that object and parameter have in common
//       returns empty string if no common movie
string Actor::connect(Actor a)
{
    int index = 0;
    string common = "";
    while(index < movies.get_length())
    {
        if(a.inMovie(movies.get_value_at(index)))
            common = movies.get_value_at(index);

        index++;
    }

    return common;
}

// Function: getName
// Input: none
// Returns: string
// Does: returns name
string Actor::getName()
{
    return name;
}

// Function: setName
// Input: String
// Returns: nothing
// Does: changes name to parameter
void Actor::setName(string n)
{
    name = n;
}

//bool operator for ==
bool Actor::operator ==(const Actor& b)
{
    return (name == b.name);
}

//bool operator for !=
bool Actor::operator !=(const Actor& b)
{
    return (name != b.name);
}

//bool operator for <<
ostream& operator <<(ostream& a, const Actor &b)
{
    a << b.name;
    return a;
}

//you need moreasdfjkl;qweruiopzxcvnm,.
