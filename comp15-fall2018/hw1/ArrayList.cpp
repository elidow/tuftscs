//Eli Dow
//9/17/18
//hw1

/*
 * Array.cpp
 * COMP15
 * Fall 2018
 *
 * Implementation for Arrrrrrray of Pirates
 */

#include "ArrayList.h"
#include <iostream>
using namespace std;

// Default constructor
// Length and current position default to 0
ArrayList::ArrayList()
{
    length = 0;
    curr_pos = 0;
    capacity = MAX_PIRATES;
    pirates = new Pirate[MAX_PIRATES];
}

//Destructor
//Deletes dynamic pirates array
ArrayList::~ArrayList()
{
    delete []pirates;
}

// Function find_pirate
// Inputs: Pirate object, bool by reference
// Returns: Pirate object
// Does: Looks for pirate in the array, modifies bool if found
//       Returns the object from the list and not the passed one
//       (In case they're different.)
Pirate ArrayList::find_pirate(Pirate p, bool &found) const
{
    int location = 0;

    while ((location < length) && !found)
    {
        if (p == pirates[location])
        {
            found = true;
            p = pirates[location];
            break;
        }
        location++;
    }
    return p;
}

// Function insert_pirate
// Inputs: Pirate object
// Returns: Nothing
// Does: Adds Pirate to end of array, increases length
//       if the pirate is unique
void ArrayList::insert_pirate(Pirate p)
{
    expand();
    
    bool found = false;
    Pirate x = find_pirate(p, found);
    
    if (found != true)
    {
        pirates[length] = x;
        length++;
    }

}

// Function delete_pirate
// Inputs: Pirate object
// Returns: Nothing
// Does: Deletes pirate, shifts everything else over
void ArrayList::delete_pirate(Pirate p)
{

    contract();
    bool found = false;
    Pirate x = find_pirate(p, found);
    int index;

    if(found == true)
    {
        for(int i = 0; i < length; i++)
        {
            if(pirates[i] == p)
            {
                index = i;
            }
        }

        for(int i = index; i < length - 1; i++)
        {
            pirates[i] = pirates[i+1];
        }
        length--;
    }
}

// Function expand
// Inputs: None
// Returns: Nothing
// Does: Expands the capacity of the array
//       Allocates a new array to hold double the capacity
//       Copy pirates from old into new
//       Deletes the initial array to free up the memory
//       Update pirates to point to the newly-allocated array
void ArrayList::expand()
{

    if(length >= capacity)
    {
        Pirate *pirates_new = new Pirate[2 * capacity];
        cout << "Expand to " << 2 * capacity << endl;
        for (int i = 0; i < length; i++)
        {
            pirates_new[i] = pirates[i];
        }

        delete [] pirates;

        pirates = pirates_new;

        capacity = 2 * capacity;
    }

}

// Function contract
// Inputs: None
// Returns: Nothing
// Does: Shrinks the capacity of the array
//       Allocates a new array to hold half the capacity
//       Copy pirates from old into new
//       Deletes the initial array to free up the memory
//       Update pirates to point to the newly-allocated array
void ArrayList::contract()
{
    int half = capacity / 2;
    if(length < half)
    {
        Pirate *pirates_new = new Pirate[half];

        cout << "Contract to " << half << endl;
        for (int i = 0; i < length; i++)
        {
            pirates_new[i] = pirates[i];
        }

        delete [] pirates;

        pirates = pirates_new;

        capacity = half;
    }

}

// Function get_next_pirate
// Input: None
// Returns: Pirate object
// Does: Returns pirate at curr_pos
//       Increments curr_pos, but wraps around
Pirate ArrayList::get_next_pirate()
{
    Pirate p = pirates[curr_pos];
    curr_pos = (curr_pos + 1) % length;
    return p;
}

// Function make_empty
// Input: none
// Returns: none
// Does: sets length to 0 (memory not modified)
void ArrayList::make_empty()
{
    length = 0;
}

// Function reset_array
// Input: none
// Returns: none
// Does: sets curr_pos to 0 
void ArrayList::reset_array()
{
    curr_pos = 0;
}

// Function print
// Input: none, const
// Returns: none
// Does: Prints array from 0 to length
void ArrayList::print(ostream &o) const 
{
    //make reference of an ostream 
    for (int i = 0; i < length; i++)
    {
        pirates[i].print(o);
        //o << "," << endl;
    }
}

// Function is_full
// Input: none, const
// Returns: bool
// Does: Compares actual length to capacity
// bool ArrayList::is_full() const
// {
//     return (length >= MAX_PIRATES-1);
// }

// Function get_length
// Input: none, oncst
// Returns: int
// Does: Returns the value in length attribute
int ArrayList::get_length() const
{
    return length;
}
