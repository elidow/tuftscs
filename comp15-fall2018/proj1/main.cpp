//Eli Dow
//10/21/18
//Driver for proj1


#include <iostream>
#include <string>
#include <cstdio>
#include <fstream>
#include <math.h>

#include "Trie.h"

using namespace std;

int main(int argc, char *argv[])
{
    string input_name;
    ifstream inputFile;

    string output_name;
    ofstream outputFile;
    
    string command = "";
    string function = "";
    string sequence = "";

    if (argc<3) 
    {
        cout << "Error, this function needs 2 parameters:\n";
        cout << "1-The query file\n";
        cout << "2-The output location\n";
    }
    else 
    {

        Trie collection;

        input_name = argv[1];
        inputFile.open(input_name.c_str());

        if (!inputFile.is_open()) 
        {
            cerr << "Unable to open input file " << input_name << "\n";
            return 1;
        }

        output_name = argv[2];
        outputFile.open(output_name.c_str());
        
        if (!outputFile.is_open())
        {
            cerr << "Unable to open output file " << output_name << "\n";
            return 1;
        }

        else
        {
          	while(getline(inputFile, command))
            {
                function = command[0];

                for(int i = 2; i < command.size(); i++)
                    sequence += command[i];

                if(function == "i")
                {
                    //cerr << "insert!" << endl;
                    collection.insert(sequence);
                }
                else
                {

                    if(function == "q")
                    {
                        //cerr << "query!" << endl;
                        outputFile << collection.query(sequence) << endl;
                    }

                    else
                    {
                        //cerr << "remove!" << endl;
                        string remove = "";
                        remove = collection.remove(sequence);
                        remove = remove.substr(0,remove.size()-1);
                        outputFile << remove << endl;
                    }
                }

                sequence = "";               
            }
            //cerr << "let's print!" << endl;
            //collection.print_trie();
            
            inputFile.close();
            outputFile.close();
        }
    }
}  //int main