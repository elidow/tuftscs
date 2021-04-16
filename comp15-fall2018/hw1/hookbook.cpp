//Eli Dow
//9/17/18
//hw1

/* 
 * hookbook.cpp
 * COMP15
 * Fall 2018
 *
 * Driver for ye treasure map
 */

#include <iostream>
#include <string>
#include "Pirate.h"
#include "ArrayList.h"
#include "PirateMates.h"
using namespace std;

const int ALL_PIRATES = 697;
const string TEST = "pirate_test.txt";
const string PIRATE_FILE = "pirate_names.txt";
const string OUTPUT_ONE = "mypirate_one_friend.txt";
const string OUTPUT_TWO = "mypirate_no_friends.txt";
const string OUTPUT_THREE = "myall_pirates_all_friends.txt";

int all_pirates_smee(PirateMates [], Pirate);
void all_pirates_deleted(PirateMates [], Pirate, int);
void all_pirates_all_friends(PirateMates [], int);

int main()
{

    cout << "Welcome to Hookbook, Matey!\n";
    PirateMates hookbook[ALL_PIRATES];

    Pirate smee("Smee");

    // Step one: Every pirate is friends only with Smee
    int num_pirates = all_pirates_smee(hookbook, smee);

    // Step two: Delete Smee, no one has any friends
    all_pirates_deleted(hookbook, smee, num_pirates);

    // Step three: Every pirate is friends with every other
    all_pirates_all_friends(hookbook, num_pirates);
    cout << "Hookbook complete! Check your "
         << "output files and yo ho ho.\n";

    return 0;
}

int all_pirates_smee(PirateMates hookbook[], Pirate smee)
{
    int counter = 0;

    // Step one: Every Pirate is friends with Smee
    // Make an ArrayList out of every Pirate in the txt file
    ifstream infile;
    infile.open(PIRATE_FILE.c_str());
    if (!infile.is_open())
    {
        cerr << "Could not add pirates from file\n";
        return -1;
    }

    while (!infile.eof() && counter < ALL_PIRATES)
    {
        Pirate p;
        p.generate_next_pirate(infile);
        p.assign_pirate_id();
        hookbook[counter].pirate = p;
        hookbook[counter].mates.insert_pirate(smee);
        counter++;
    }

    infile.close();

    // Print all the pirates and friends
    ofstream outfile;
    outfile.open(OUTPUT_ONE.c_str());
    for (int i = 0; i < counter; i++)
    {
        hookbook[i].pirate.print(outfile);
        outfile << ": ";
        hookbook[i].mates.print(outfile);
        outfile << endl;
    }
    outfile.close();
    return counter;
}

void all_pirates_deleted(PirateMates hookbook[], Pirate p, int counter)
{
    // Delete Smee, who is friends with everyone, plus a made-up pirate
    // Makes sure the delete works if the pirate's there or not
    Pirate fake("Fakey");
    for (int i = 0; i < counter; i++)
    {
        hookbook[i].mates.delete_pirate(p);
        hookbook[i].mates.delete_pirate(fake);
    }

    // Print all to a new file
    ofstream outfile;
    outfile.open(OUTPUT_TWO.c_str());
    for (int i = 0; i < counter; i++)
    {
        hookbook[i].pirate.print(outfile);
        outfile << ": ";
        hookbook[i].mates.print(outfile);
        outfile << endl;
    }
    outfile.close();
}

void all_pirates_all_friends(PirateMates hookbook[], int num_pirates)
{

    for (int i = 0; i < num_pirates; i++)
    {
        for (int j = 0; j < num_pirates; j++)
        {
            // I can't be friends with myself
            if (hookbook[i].pirate == hookbook[j].pirate)
                continue;
            
            hookbook[i].mates.insert_pirate(hookbook[j].pirate);
       
        }

        
    }

    
    // Print all to a new file
    ofstream outfile;
    outfile.open(OUTPUT_THREE.c_str());
    for (int i = 0; i < num_pirates; i++)
    {
        hookbook[i].pirate.print(outfile);
        outfile << ": ";
        hookbook[i].mates.print(outfile);
        outfile << endl;
    }
    
    outfile.close();
}

