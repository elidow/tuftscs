/*
 * Filename: Index.h
 * Contains: Interface of the Index class 
 * Part of: Project 2 assignment "Grep" for Comp 15 Fall 2018
 *
 */

#ifndef INDEX_H
#define INDEX_H

#include <vector>
#include <string>
#include <iostream>
#include <cstdio>

using namespace std;

#include "DirNode.h"
#include "LinkedList.h"
#include "DataType.h"
#include "NodeType.h"
#include "StringProcessing.h"

class Index{

public:
    // Default constructor. Creates empty array
    Index();

    ~Index();

    // copy constructor (written for you)
    Index(const Index &source);

    // assignment overload
    Index &operator= (const Index &source);

    //other public functions
    void insert(string path);

    string search(string key);


private:
    //private attributes
    int buckets;        //number of buckets(DA size)
    int words;          //keeps track of unique words in table
    LinkedList<DataType> *table;    //DA of LinkedLists
                                    //The LinkedLists are of type DataType

    //private helper functions

    void insert_word(string current, unsigned int hashed, string line,
        string path, int line_number);

    unsigned int hash_string(string key);

    void expand();

};


#endif //REFERENCE_DIRNODE_H