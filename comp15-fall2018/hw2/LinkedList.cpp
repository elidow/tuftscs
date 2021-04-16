/*
 * LinkedList.cpp
 * COMP15
 * Fall 2018
 * 
 * Implementation for Linked List of Green Line Extension Stations
 */

#include "LinkedList.h"
#include <iostream>
using namespace std;

// Default constructor
LinkedList::LinkedList()
{
    length = 0;
    head = NULL;
    curr_pos = NULL;
}

// Destructor
LinkedList::~LinkedList() 
{
    make_empty();   
}

// Assignment operator
LinkedList & LinkedList::operator = (const LinkedList &l)
{
    NodeType *temp;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
    }
    length = l.length;
    curr_pos = NULL;
    if (l.head == NULL)
        head = NULL;
    else
    {
        head = new NodeType;
        head->info = l.head->info;
        head->next = NULL;
        NodeType *curr = head;
        NodeType *orig = l.head;
        while (orig->next != NULL)
        {
            curr->next = new NodeType;
            curr->next->info = orig->next->info;
            curr->next->next = NULL;
            orig = orig->next;
            curr = curr->next;
        }
    }
    return *this;
}

// Function: get_length
// Input: nothing
// Returns: the length
// Does: returns the length of the LL
int LinkedList::get_length() const
{
    return length;
}

// Function: insert_station
// Input: Station object
// Returns: Nothing
// Does: Inserts station to the head of the list
void LinkedList::insert_station(Station s)
{
    NodeType *temp = new NodeType;
    temp->info = s;
    temp->next = head;
    head = temp;

    length++;
}

// Function: remove_station
// Input: Station object
// Returns: Nothing
// Does: Deletes the first instance of a station equal to the input
//       Also, deallocates memory of deleted station and
//       function works even if station is not in the list
void LinkedList::remove_station(Station s)
{
    
    if(head == NULL)
    {
        return;
    }

    if(head->info.is_equal(s))
    {
        NodeType *temp = head;
        head = head->next;
        delete temp;
        length--;
        return;
    }


    NodeType *temp = head->next;
    NodeType *prev = head;
    while (temp != NULL)
    {
        if(temp->info.is_equal(s))
        {
            prev->next = temp->next;
            delete temp;
            length--;
            break;
        }

        temp = temp->next;
        prev = prev->next;
    }

}


// Function: get_next_station
// Input: Nothing
// Returns: Station object
// Does: Uses curr_pos to get the next station from the list every time
//       First time this function runs, it returns the first station in the
//       list and makes curr_pos point to the next station
//       If curr_pos is pointing to the last element, it is set to the head
Station LinkedList::get_next_station()
{
    if(curr_pos == NULL)
    {
        curr_pos = head->next;
        return head->info;
    }

    else
    {
        NodeType *temp = curr_pos;

        if(curr_pos->next == NULL)
            curr_pos = head;
        else
            curr_pos = curr_pos->next;

        return temp->info;
    }
}

// Function:reset_curr_pos
// Input: Nothing
// Returns: Nothing
// Does: resets the current position to NULL
void LinkedList::reset_curr_pos()
{
   curr_pos = NULL;
}

// Function: make_empty
// Input: Nothing
// Returns: Nothing
// Does: deletes all elements in the list and deallocate any allocated memory
void LinkedList::make_empty()
{
    while(head != NULL)
    {
        NodeType *temp = head;
        head = head->next;
        delete temp;
    }
}



// Function: print
// Input: ostream object
// Returns: Nothing
// Does: prints all the stations into the given ostream object
//       along with its name and access, it outputs the distance from
//       the final stop and tracks("==") between tracks
void LinkedList::print(ostream &out)
{
    NodeType *temp = head;
    int distance = length - 1;
    while(temp != NULL)
    {

        temp->info.print(out);
        out << " " << distance;
        if(distance > 0)
        out << " == ";
        temp = temp->next;
        distance--;
    }
    out << endl;


}



