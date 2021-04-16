/*
 * CheckoutQueue.cpp
 * COMP15
 * Fall 2018
 *
 * Implementation of the CheckoutQueue class
 *
 */

#include <iostream>
#include "CheckoutQueue.h"

using namespace std;

// Function: Default Constructor
// Input: Nothing
// Returns: Nothing
// Does: Default Constructor
CheckoutQueue::CheckoutQueue()
{
	length = 0;
    head = NULL;
    back = NULL;
}

// Function: Destructor
// Input: Nothing
// Returns: Nothing
// Does: Deletes whole structure and liberates any space occupied by the queue
CheckoutQueue::~CheckoutQueue()
{
	while(head != NULL)
    {
        NodeType *temp = head;
        head = head->next;
        delete temp;
    }
}

// Function: isEmpty
// Input: Nothing
// Returns: Boolean value
// Does: returns a boolean value that is true if this instance of the
//       CheckoutQueue class is empty
bool CheckoutQueue::isEmpty()
{
	if(head == NULL)
		return true;
	else
		return false;	
}

// Function: size
// Input: Nothing
// Returns: integer value
// Does: returns an integer that represents the number of shoppers in the queue.
int CheckoutQueue::size()
{
	if(isEmpty())
		return 0;
	else
	{
		NodeType *temp = head;
		int total_shoppers = 0;
		while(temp != NULL)
		{
			total_shoppers++;
			temp = temp->next;
		}

		return total_shoppers;
	}
}


// Function: totalItems
// Input: Nothing
// Returns: integer value
// Does: returns an integer value that is the sum of the items of every 
//       shopper in the queue
int CheckoutQueue::totalItems()
{
	if(isEmpty())
		return 0;
	else
	{
		NodeType *temp = head;
		int total_items = 0;
		while(temp != NULL)
		{
			int items = temp->info.num_items;
			total_items += items;
			temp = temp->next;
		}

		return total_items;
	}
}

// Function: enqueque
// Input: Shopper object
// Returns: Nothing
// Does: adds Shopper object to the end of the queue
void CheckoutQueue::enqueue(Shopper toAdd)	
{
	NodeType *temp = new NodeType;
	temp->info = toAdd;
	if(head == NULL)
	{
		temp->next = head;
		head = temp;
		back = temp;
	}
	
	else
	{
		temp->next = back->next;
		back->next = temp;
    	back = temp;
	}
	

    length++;
}

// Function: front
// Input: Nothing
// Returns: Reference of a Shopper object
// Does: returns a reference to the front element in the queue
//       If the queue is empty, it throws a C++ runtime error message
Shopper &CheckoutQueue::front()
{
	if(head == NULL)
	{
		throw runtime_error("empty_queue");
	}
	else
	{
		NodeType *temp = head;
		return temp->info;
	}
}

// Function: dequeue
// Input: Nothing
// Returns: Nothing
// Does: Removes the element at the front of the queue, if the queue is empty 
//	     it throws a C++ runtime error
void CheckoutQueue::dequeue()
{
	//print();
	NodeType *temp = head;
	if(head == NULL)
	{
		throw runtime_error("empty_queue");
	}
	else
	{
		head = head->next;
		delete temp;
	}
	length--;
	
}

// Function: print
// Input: Nothing
// Returns: Nothing
// Does: Prints each element's id and number of items
//		 Function is private because it is only called when debugging
void CheckoutQueue::print()
{
    NodeType *temp = head;
    while(temp != NULL)
    {
        cerr << temp->info.id << " " << temp->info.num_items;
        cerr << " " << temp->info.arrival_time << endl;
        temp = temp->next;

    }
    cerr << endl;

}

