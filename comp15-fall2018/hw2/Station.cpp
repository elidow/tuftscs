/* 
 * Station.cpp
 * COMP15
 * Fall 2018
 *
 * Implementation of the Station class for homework 2
 */

#include "Station.h"
#include <iostream>
using namespace std;

// Constructor
Station::Station()
{
	name = "NoName";
    access = false;
}

// Parameterized Constructor
Station::Station(string input_name, bool input_access)
{
    name = input_name;
    access = input_access;
}


// Function: is_equal
// Input: Station object
// Returns: bool
// Does: Returns true if the station's object
// 		 contains the same info(name and access) as 
//		 the one given by parameter
//       Otherwise, returns false
bool Station::is_equal(Station s)
{
    if(name == s.getName() && access == s.getAccess())
    	return true;
    else
    	return false;
}

// Function: print
// Input: Ostream pointer
// Returns: Nothing
// Does: Prints a string containing the station
//		 and whether is is available(A) or not(U)
void Station::print(ostream &outfile)
{
	string letter = "U";
	if(access == true)
		letter = "A";
	outfile << "" + name + " " + letter;
}


