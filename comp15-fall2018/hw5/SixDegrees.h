/*
 * Filename: Actor.h
 * Contains: Interface of the template Actor class 
 * Part of: Homework 5 assignment "Graph Traversal" for Comp 15 Fall 2018
 */


#include "Graph.h"
#include "Actor.h"
#include "LinkedList.h"
#include <iostream>
#include <ostream>
#include <string>
using namespace std;

#ifndef SIXDEGREES_H_
#define SIXDEGREES_H_


// wrapper functions
//template<class Vertex>
//int index_is(Vertex *vertices, Vertex v);

//template<class Vertex>
class SixDegrees
{
public:
    //Constructor functions
    SixDegrees();

    //Destructor
    // _SixDegrees();

    // Functions needed to modify the graph
    void populate_graph(istream &in); //populates graph from a file
    void run(istream &in, ostream &out); //runs the program

private:
    // int num_vertices;       // number of vertices of the graph
    // Vertex *vertices;       // stores label of vertices, if any
    // int **edges;            // weighted 2-D array to store edges 


    // int *path;              // array used to store a path
    // int curr_vertex;        // variable to track current vertex in DFS
    // bool *marks;            // 2-D array of vertices to 
    Graph <Actor> g;
    void BFS(Actor a, Actor b, ostream &out);
};

#endif