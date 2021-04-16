//Eli Dow
//9/17/18
//hw1

/*
 * Pirate.cpp
 * COMP15
 * Fall 2018
 *
 * Implarrrrrrmentation of a Pirate
 */

#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include "Pirate.h"
using namespace std;

int Pirate::pirate_count = 0;

Pirate::Pirate()
{
    pirate_id = -1;
    name = "Cap'n Hook";
}

Pirate::Pirate(string n)
{
    assign_pirate_id();
    name = n;
}

//accepts a ostream so client print a pirate to a file
void Pirate::print(ostream &o) const
{
    o << pirate_id << " "
         << name;
}


void Pirate::generate_pirate_name(ifstream &infile, int range)
{
    string pname;
    int rando = rand() % range;
    int count = 0;

    infile.clear();
    infile.seekg(0, ios::beg);
    while (getline(infile, pname))
    {
        if (count == rando)
        {
            name = pname;
            break;
        }
        count++;
    }
}

// Function generate_next_pirate
// Inputs: fstream &infile
// Returns: Nothing
// Does: Sets name(in the Pirate class) to the next pirate in
//       pirate_names.txt
void Pirate::generate_next_pirate(ifstream &infile)
{
    string pname;
    getline(infile, pname);

    if(pname != "-1")
    {
        name = pname;
    }

}

void Pirate::assign_pirate_id()
{
    pirate_id = pirate_count++;
}

bool operator == (const Pirate &p1, const Pirate &p2)
{
    return (p1.pirate_id == p2.pirate_id);
}

