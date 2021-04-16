/*
 * CheckoutQueue.h
 * COMP15
 * Fall 2018
 *
 * Driver for homework 3
 *
 */


#include <iostream>
#include <string>
#include <cstdio>
#include <fstream>
#include "GrocerySim.h"

using namespace std;


// Function:got_int
// Input:  string and pointer to a number
// Returns: true if the string contains a number inside
// Does: scans the string for a number. If found it will
//       set the value of resultp equal to it
bool got_int(string s, int *resultp)
{
        return sscanf(s.c_str(), "%d", resultp) == 1;
}
		
// Function: main
// Input: 4 or 5 parameters (see below)
// Returns: 0 if no problems were found, 1 otherwise
// Does: Main driver for testing GrocerySim class

int main(int argc, char *argv[])
{
    string filename;
    ifstream inputFile;
    int std_queue, exp_queue, max_exp;
    bool all_ok;

    if (argc<4) 
    {
        cout << "Error, this function needs at least 3 parameters:\n";
        cout << "1-The number of standard queues\n";
        cout << "2-The number of express queues\n";
        cout << "3-The maximum number of allowed items per queue\n";
        cout << "4-(Optional) data to be used as input\n";
    }
    else 
    {
        //We extract the parameters from the input
        all_ok = got_int(argv[1],&std_queue);
        all_ok = (all_ok && got_int(argv[2],&exp_queue));
        all_ok = (all_ok && got_int(argv[3],&max_exp));

        if (not(all_ok)){
            cerr << "Error. Input does not contain 3 numbers\n";
            return 1;
        }
        GrocerySim store(std_queue,exp_queue,max_exp);
      
        //In order to run the Grocery Simulator we reed from either
        //cin or the parameter given when executing the command line
        if (argc == 4) 
        {
            store.run(cin);            
        }
        else //We need to open the file and give it as part   
        {    //of the input to our simulator
            filename= argv[4];
            inputFile.open(filename);
            if (not inputFile.is_open()) 
            {
                cerr << "Unable to open file " << filename << "\n";
                return 1;
            }
            else
            {
            store.run(inputFile);
            inputFile.close();
            }         
        }//else (5 or more parameters)   
    }//else (4 or more parameters)
}  //int main