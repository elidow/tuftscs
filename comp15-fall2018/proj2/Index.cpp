/*
 * Index.cpp
 */

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>

#include "Index.h"
#include "DirNode.h"

using namespace std;

//constructor
Index::Index()
{
    buckets = 100000;
    words = 0;
    table = new LinkedList<DataType>[buckets]();
}

//destructor
Index::~Index()
{
    for(int i = 0; i < buckets; i++)
    {
        table[i].make_empty();
    }
    delete []table;
}

// copy constructor
Index::Index(const Index &source)
{
    buckets = source.buckets;
    words = source.words;
    table = new LinkedList<DataType>[buckets]();
    for(int i = 0; i < buckets; i++)
    {
        int j = 0;
        while(j < source.table[i].get_length())
        {
            table[i].get_value_at(j) = source.table[i].get_value_at(j);
            j++;
        }
    }
}

// assignment overload
Index &Index::operator= (const Index &source)
{

    if(this != &source)
    {
        for(int i = 0; i < buckets; i++)
        {
            table[i].make_empty();
        }
        table->make_empty();

        buckets = source.buckets;
        words = source.words;
        table = new LinkedList<DataType>[buckets]();
        for(int i = 0; i < buckets; i++)
        {
            int j = 0;
            while(j < source.table[i].get_length())
            {
                table[i].get_value_at(j) = source.table[i].get_value_at(j);
                j++;
            }
        }

    }

    return *this;
}

// Function: insert
// Input: string
// Returns: Nothing
// Does: inserts words from a file into a hash table
//       calls hashing function and helper when if finds a full word
//       also expands
void Index::insert(string path){
    ifstream inputFile;
    string line = "";
    string temp = "";
    inputFile.open(path.c_str());
    if (!inputFile.is_open()) 
        cerr << "Could not build index, exiting." << "\n";
    else{
        string current = "";
        unsigned int hashed = 0;
        StringProcessing word_finder;
        int line_number = 1;
        while(getline(inputFile, line)){
            temp = word_finder.getWords(line);
            for(int i = 0; i < temp.length(); i++)
            {
                if(temp.substr(i,1).compare(" ") != 0)
                    current += temp.substr(i,1);
                else
                {
                    hashed = hash_string(current);
                    insert_word(current, hashed, line, path, line_number);
                    current = "";
                }                 
            }
            line_number++;
            expand();
        }
    }
    return;
}

// Function: insert_word
// Input: string, unsigned int, string, string, int
// Returns: Nothing
// Does: checks to see if word(first string) is in the hash table
//       if it is, creates a new DataType object and inserts it(with hash)
//       whether the word exists or not, it updates the word's appearances
//       with the the last three parameters
void Index::insert_word(string current, unsigned int hashed, string line,
    string path, int line_number)
{
    int j = 0;
    bool new_word = true;

    while(j < table[hashed].get_length())
    {
        if(current == table[hashed].get_value_at(j).getWord())
        {
            table[hashed].get_value_at(j).addFile_Line(path, line_number, line);
            new_word = false;
        }
        j++;
    }
    if(new_word)
    {

        DataType d(current);
        d.addFile_Line(path, line_number, line);
        table[hashed].insert(d);
        words++;
    }
    current = "";
    new_word = true;
}


// Function: hash_string
// Input: string
// Returns: unsigned int
// Does: finds hash value of paticular string(key)
unsigned int Index::hash_string(string key)
{
    std::hash<std::string> str_hash;
    size_t temp = str_hash(key);
    return temp % buckets;
}

// Function: search
// Input: string
// Returns: string
// Does: searches hash table for word with hash function
//       puts all lines into one string, returns that string
string Index::search(string key)
{
    string output, prev, temp = "";
    unsigned int hashed = 0;
    hashed = hash_string(key);
    bool found = false;
    int i = 0;
    while(i < table[hashed].get_length())
    {

        if(key == table[hashed].get_value_at(i).getWord())
        {

            for(int j = 0; j < table[hashed].get_value_at(i).numPlaces(); j++)
            {
                temp = table[hashed].get_value_at(i).getPlace(j);
                if(temp.compare(prev) != 0)
                    output += temp + "\n";
                prev = temp;
            }
            found = true;
        }
        i++;
    }
    
    if(!found)
        return "query not found";

    return output;
}

// Function: expand
// Input: Nothing
// Returns: Nothing
// Does: if load factor > .75, creates a DA twice the origianl size
//       Then, redistributes DataType objects into hash table
void Index::expand()
{
    if((((double) words) / ((double) buckets)) > 0.75)
    {
        int temp = buckets;
        buckets = buckets * 2;
        LinkedList<DataType> *new_table = new LinkedList<DataType>[buckets]();
        unsigned int hashed = 0;
        for(int i = 0; i < temp; i++)
        {
            int j = 0;
            while(j < table[i].get_length())
            {
                hashed = hash_string(table[i].get_value_at(j).getWord());
                new_table[hashed].insert(table[i].get_value_at(j));
                j++;
            }
        }

        for(int i = 0; i < temp; i++)
        {
            table[i].make_empty();
        }
        delete []table;

        table = new_table;
    }
    return;
}