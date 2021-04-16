/*
 * Filename: Graph.cpp
 * Contains: Implementation of the template Graph class 
 * Part of: Homework 5 assignment "Graph Traversal" for Comp 15 Fall 2018
 *
 */

#include <iostream>
#include <ostream>
#include <string>
#include "SixDegrees.h"
using namespace std;

// Function: constructor
// Parameters: none
// Returns: nothing
// Does: default constructor
SixDegrees::SixDegrees()
{
   g.initialize_graph(1000);
}

// SixDegrees::~SixDegrees()
// {
// 	delete g;
// }

// Function: initialize_graph
// Parameters: istream
// Returns: nothing
// Does: initializing
void SixDegrees::populate_graph(istream &in)
{

    Actor *people[1000];
    string line = "";
    int index = 0;
    bool actor = true;
    string common = "";
    while(getline(in, line))
    {
    	if(line.compare("*") == 0)
    	{
    		g.add_vertex(*people[index]);
    		for(int i = 0; i < index; i++)
    		{
    			common = people[index]->connect(*people[i]);
    			if(common.compare("") != 0)
    			{
        			g.add_edge(*people[index], *people[i], common);
        			g.add_edge(*people[i], *people[index], common);
    			}
    		}
    		index++;
    		common = "";
    		actor = true;
    	}
    	else
    	{
    		if(actor)
    			people[index] = new Actor(line);
    		else
    			people[index]->insertMovie(line);
    		actor = false;
    	}
    }
}


// Function: run
// Input: istream and ostream objects
// Returns: nothing
// Does: runs the program and graph, calls BFS
void SixDegrees::run(istream &in, ostream &out)
{
	out << "Enter two actor names seperated by a new line" << endl;
    out << "Press ctrl-D to quit" << endl;
    Actor a;
    Actor b;
    bool second = false;
    string name1;
    string name2;
    string line = "";
    while(getline(in, line))
    {
    	name1 = line;
    	a = Actor(name1);
    	if(!g.is_vertex(a))
            	out << "Sorry, " << a.getName() << " is not in the list\n";
        else
        {
        	while(!second){
	        	getline(in, name2);
		    	b = Actor(name2);

		    	if(!g.is_vertex(b))
		            out << "Sorry, " << b.getName() << " is not in the list\n";
		    	else
		    	{
		    		second = true;
			    	BFS(a,b,out);
			    }
			}
		}
		second = false;
	    out << endl;
    }
}

// Function: BFS
// Input: two Actor objects and an ostream object
// Returns: nothing
// Does: uses Breadth-First search to find and print
//       a path from Actor a to Actor b
void SixDegrees::BFS(Actor a, Actor b, ostream &out)
{
	g.clear_marks();
    g.initialize_path();

    Queue <Actor>one;
    Queue <Actor>two;

    Actor current;
    one.enqueue(a);
    bool found = false;
    Actor neighbor;
    while(!one.is_empty())
    {
        one.dequeue(current);
        if(!g.is_marked(current))
        {
            g.mark_vertex(current);
            g.get_to_vertices(current, two);
            while(!two.is_empty())
            {
                two.dequeue(neighbor);
                g.update_predecessor(current, neighbor);
                one.enqueue(neighbor);
                if(neighbor == b)
                    found = true;
            }

        }
    }
    g.report_path(out, a, b);
    return;
}