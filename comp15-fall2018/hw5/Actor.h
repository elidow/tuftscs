/*
 * Filename: Actor.h
 * Contains: Interface of the template Actor class 
 * Part of: Homework 5 assignment "Graph Traversal" for Comp 15 Fall 2018
 */

#include "LinkedList.h"
#include <iostream>
#include <ostream>
#include <string>

#ifndef ACTOR_H_
#define ACTOR_H_

using namespace std;

class Actor
{
public:
    //Constructor functions
    Actor();
    Actor(string);

    // Functions needed to modify the graph
    void insertMovie(string);
    bool inMovie(string);
    string connect(Actor);

    //Overloading operators
    bool operator ==(const Actor &b);
    bool operator !=(const Actor &b);
    friend ostream& operator <<(ostream& a, const Actor& b);

    string getName();
    void setName(string);

private:
    string name;
    LinkedList <string> movies;
};

#endif