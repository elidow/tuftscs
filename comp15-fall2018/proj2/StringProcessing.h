/*
 * Filename: StringProcessing.h
 * Contains: Interface of the StringProcessing class 
 * Part of: Project 2 assignment "Grep" for Comp 15 Fall 2018
 *
 */

#ifndef STRINGPROCESSING_H
#define STRINGPROCESSING_H

#include <string>
#include <iostream>

using namespace std;

class StringProcessing{

public:
    // Default constructor. Creates empty array
    StringProcessing();

    //Functions
    string getWords(string);


private:
    string words;	//words
    
};


#endif