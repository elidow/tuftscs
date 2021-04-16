//Eli Dow
//10/21/18
//StringProcessing.cpp


#include <iostream>
#include <string>

using namespace std;

#include "StringProcessing.h"

//constructor
StringProcessing::StringProcessing()
{
    words = "";
}

// Function: getWords
// Input: string
// Returns: string
// Does: returns a string of all the words in line, separated by spaces
string StringProcessing::getWords(string line)
{
    int first = -1;
    bool word = false;
    int last = -1;
    words = "";
    for(int i = 0; i < line.length(); i++)
    {
        if(isalnum(line[i]))
        {
            if(!word)
            {
                word = true;
                first = i;
            }
            last = i;
        }

        else
        {
            if(line.substr(i, 1).compare(" ") == 0)
            {
                if((first != -1) && (last != -1))
                    words += line.substr(first, (last - first + 1)) + " ";
                word = false;
                first = -1;
                last = -1;
            }
        }
    }

    if((first != -1) && (last != -1))
        words += line.substr(first, (last - first + 1)) + " ";
    return words;
}