/*
 * Filename: main.cpp
 * Contains: Driver for homework 5 
 * Part of: Homework 5 assignment "Graph Traversal" for Comp 15 Fall 2018
 *
 */

#include <iostream>
#include <ostream>
#include <fstream>
#include <cstdlib>
#include "SixDegrees.h"

using namespace std;

int main(int argc, char *argv[])
{

    string actor_name;
    ifstream actorFile;

    actor_name = "actors.txt";
    actorFile.open(actor_name.c_str());

    if (!actorFile.is_open()) 
    {
        cerr << "Unable to open input file " << actor_name << "\n";
        return 1;
    }

    else
    {
        SixDegrees sd;
        sd.populate_graph(actorFile);

        if (argc<2)
        {
            sd.run(cin, cout); 
        }

        else
        {
            string input_name;
            ifstream inputFile;

            input_name = argv[1];
            inputFile.open(input_name.c_str());

            if (!inputFile.is_open()) 
            {
                cerr << "Unable to open input file " << input_name << "\n";
                return 1;
            }

            else
            {
                sd.run(inputFile, cout);
            }
        }

    }

 
    return 0;
}
