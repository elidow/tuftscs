/*
 * Filename: test-graph.cpp
 * Contains: driver for unti-testing for homework 5
 * Part of: Homework 5 assignment "Graph Traversal" for Comp 15 Fall 2018
 *
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "SixDegrees.h"
#include "Graph.h"
#include "NodeType.h"
#include "Queue.h"
#include "Actor.h"

using namespace std;

int main(int argc, char *argv[])
{
    // if (argc<2)
    // {
    // 	SixDegrees sd;
    // 	sd.run(cin, cout); 
    // }
   
   	// if (argc<3)
   	// {
   	// 	string input_name;
    // 	ifstream inputFile;

    // 	input_name = argv[1];
    //     inputFile.open(input_name.c_str());

    //     if (!inputFile.is_open())
    //     {
    //         cerr << "Unable to open input file " << input_name << "\n";
    //         return 1;
    //     }

    //     else
    //     {
	   // 		SixDegrees = sd;
	   // 		sd.run(inputFile, cout);
	   // 	}
   	// }

    SixDegrees s;

    Graph<Actor> g;

    Testing Actor class functions
    Actor a("Aaron");
    a.insertMovie("Cars");
    a.insertMovie("Cars2");
    a.insertMovie("Cars3");
    if(a.inMovie("Cars"))
        cerr << "Check 1 good" << endl;
    if(!a.inMovie("Trucks"))
        cerr << "Check 2 good" << endl;
    a.insertMovie("Cars4");
    if(a.inMovie("Cars4"))
        cerr << "Check 3 good" << endl;

    Actor b("Brad");
    b.insertMovie("Howard the Duck");
    b.insertMovie("Cars3");
    string common = a.connect(b);
    if(common.compare("") != 0)
    {
        cerr << "" << a.getName() << " and " << b.getName() << " were both in ";
        cerr << common << "." << endl;
    }
    else
    {
        cerr << "" << a.getName() << " and " << b.getName() << " have no movie ";
        cerr << "in common." << endl;
    }

    Actor a("Aaron");
    Actor b("Brad");

    // //Testing Graph class
    g.initialize_graph(1000);
    cerr << "yikes" << endl;
    g.add_vertex(a);
    g.add_vertex(b);
    cerr << "Added vertices" << endl;
    g.add_edge(a, b, "Cars3");
    string mov = "";
    mov = g.get_edge(a , b);
    cerr << mov << endl;
    g.report_path(cout, a, b);

    Actor c("Chad");
    //a.insertMovie("Cars3");
    g.add_vertex(c);
    g.add_edge(b, c, "FratBoys");
    cerr << "Inserting vertix and edge good" << endl;
   
    g.report_path(cout, a, c);

    //s.run(cin, cout);



 
    return 0;

}