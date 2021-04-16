/*
 * DataType.cpp
 */

#include <vector>
#include <string>
#include <iostream>

using namespace std;

#include "DataType.h"

//constructor
DataType::DataType()
{
    word = "";
}

//parametrized constructor
DataType::DataType(string w)
{
    word = w;
}

//destructor
DataType::~DataType()
{
    file_line.clear();
}

// Function: getWord
// Input: Nothing
// Returns: string
// Does: returns word of object
string DataType::getWord()
{
	return word;
}

// Function: numPlaces
// Input: Nothing
// Returns: int
// Does: returns number of appearances for a word, or size of vector
int DataType::numPlaces()
{
	return file_line.size();
}

// Function: addFile_Line
// Input: string, int, string
// Returns: Nothing
// Does: concatenates parameters(file and line) and inserts it into the vector
void DataType::addFile_Line(string s, int i, string s2)
{
	string line = s + ":" + to_string(i) + ": " + s2;

	file_line.push_back(line);

	return;
}

// Function: getPlace
// Input: int
// Returns: string
// Does: returns vertex at index in parameter
string DataType::getPlace(int index)
{
	return file_line.at(index);
}

//bool operator for ==
bool DataType::operator ==(const DataType& b)
{
    return (word == b.word);
}

