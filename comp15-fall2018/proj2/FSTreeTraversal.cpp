//Eli Dow
//10/21/18
//Driver for proj2


#include <iostream>
#include <string>
#include <cstdio>
#include <fstream>
#include <math.h>

#include "FSTree.h"
#include "DirNode.h"
#include "Index.h"
#include "StringProcessing.h"

using namespace std;

//helper functions
void insert_all(DirNode *current, string path);
void call_menu();
bool quit_check(string line);
bool insensitive_check(string line);
void query_word(string word, bool insensitive);
void str_permutations(string input);

Index T;


int main(int argc, char *argv[])
{
    string input_name;

    if (argc != 2) 
    {
        cout << "usage: ./the_gerp directory" << endl;
    }
    else 
    {
        input_name = argv[1];
        FSTree object(input_name);
        if (object.isEmpty()) 
        {
            cout << "Could not build index, exiting." << "\n";
            return 1;
        }

        else
        {
            DirNode *root = object.getRoot();
            insert_all(root, input_name);
            call_menu();
        }

    }
}

// Function: insert_all
// Input: pointer to a DirNode object, string
// Returns: Nothing
// Does: traverses the directory and inserts all files into the hash table
void insert_all(DirNode *current, string path)
{
    if(current->hasSubDir())
    {
        for(int i = 0; i < current->numSubDirs(); i++)
        {
            insert_all(current->getSubDir(i),
                path + "/" + current->getSubDir(i)->getName());
        }
    }

    if(current->hasFiles())
    {
        for(int i = 0; i < current->numFiles(); i++)
            T.insert(path + "/" + current->getFile(i));
    }

}

// Function: call_menu
// Input: Nothing
// Returns: Nothing
// Does: calls query and takes in user string
//       processes string, then passes all words into helper
//       checks for insensitive cases and quit cases
void call_menu(){
    string line, current = "";
    bool insensitive = false;
    bool not_first = false;
    StringProcessing word_finder;
    cout << "Query? ";
    while(getline(cin, line)){
        line += " ";
        if(quit_check(line))
            return;    
        for(int i = 0; i < line.length(); i++){
            if(line.substr(i,1).compare(" ") != 0)
                current += line.substr(i,1);
            else{
                if(insensitive_check(current))
                    insensitive = true;
                else{
                    current = word_finder.getWords(current);
                    current = current.substr(0, current.length() - 1);
                    if(not_first)
                        cout << "Query? ";
                    else
                        not_first = true;
                    query_word(current, insensitive);
                    insensitive = false;
                }
                current = "";
            }                  
        }
        cout << "Query? ";
        insensitive = false;
        not_first = false;
    }
}

// Function: quit_check
// Input: string
// Returns: Nothing
// Does: checks to see if there is a quit query, quits if there is
bool quit_check(string line)
{
    if((line.substr(0,2).compare("@q") == 0) ||
        (line.substr(0,5).compare("@quit") == 0))
    {
        cout << "\nGoodbye! Thank you and have a nice day." << endl;
            return true;
    }
    return false;
}

// Function: insensitive_check
// Input: string
// Returns: bool
// Does: returns true if there is a case insensitive command(@i or 
//       @insensitive). returns false otherwise
bool insensitive_check(string line)
{
    if((line.substr(0,2).compare("@i") == 0) ||
        (line.substr(0,12).compare("@insensitive") == 0))
    {
        return true;
    }
    return false;
}

// Function: query_word
// Input: string, bool
// Returns: Nothing
// Does: outputs all lines that the string appears
//       considers case-sensitive/insensitive
void query_word(string word, bool insensitive)
{
    string output = "";
    if(!insensitive)
    {
        output = T.search(word);
        if(output != "query not found")
            cout << output;
        else
        {
            if(word == "")
                cout << "\"\"";
            cout << word << " Not Found. Try with @insensitive or @i." << endl;
        }
    }

    else
    {
        str_permutations(word);
    }
}

// Function: str_permutations
// Input: string
// Returns: Nothing
// Does: queries all possible permutations of upper/lower case of a string
void str_permutations(string word) 
{
    string temp = word;
    int size = 0;
    int max = 1;
    int not_found = 0;
    for(int i = 0; i < word.length(); i++)
        if(isalpha(word[i]))
            size++;
    string output;
    for(int i = 0; i < size; i++)
        max *= 2;
    for(int i = 0; i < word.length(); i++)
            if(isalpha(word[i]))
                word[i] = tolower(word[i]);
    for (int i = 0; i < max; i++) { 
        string combination = word; 
        for (int j = 0; j < size; j++)  
            if (((i >> j) & 1) == 1) 
                if(isalpha(word[j]))
                    combination[j] = toupper(word.at(j));      
  
        output = T.search(combination);
        if(output != "query not found")
            cout << output;
        else
            not_found++;
    }
    if(not_found == max)
    {
        if(temp == "")
            cout << "\"\"";
        cout << temp << " Not Found." << endl;
    }
} 

