/*
 * Filename: DataType.h
 * Contains: Interface of the DataType class 
 * Part of: Project 2 assignment "Grep" for Comp 15 Fall 2018
 *
 */

#ifndef DATATYPE_H
#define DATATYPE_H

#include <vector>
#include <string>

using namespace std;

class DataType{

public:
    // Default constructor. Creates empty array
    DataType();

    //Parametrized constructor
    DataType(string);

    //Destructor
    ~DataType();


    //public functions
    string getWord();

    int numPlaces();

    void addFile_Line(string, int, string);

    string getPlace(int);

    bool operator ==(const DataType &b);


private:
    string word;                //word
    vector<string> file_line;   //vector of strings each string is compacted
                                //of a directory, line number, and line
};


#endif //REFERENCE_DIRNODE_H