/*
 * CheckoutQueue.h
 * COMP15
 * Fall 2018
 *
 * Implementation of the CheckoutQueue class
 *
 */


#include <iostream>
#include <string>
#include <cstdio>
#include <fstream>
#include "GrocerySim.h"
#include "CheckoutQueue.h"
#include "shopper.h"


using namespace std;

GrocerySim::GrocerySim()
{

}

// Function: Parameterized Constructor
// Input: num_std, num_express, max_express
// Returns: Nothing
// Does: Parameterized Constructor for a GrocerySim object
GrocerySim::GrocerySim(int num_std, int num_express, int max_express)
{
	num_standard_lanes = num_std;
	num_express_lanes = num_express;
	max_express_items = max_express;
	lanes = new CheckoutQueue[num_standard_lanes];
	express = new CheckoutQueue[num_express_lanes];
}

// Function: Destructor
// Input: Nothing
// Returns: Nothing
// Does: Deletes memory(Not dynamically allocating memory)
GrocerySim::~GrocerySim()
{
	
}


void GrocerySim::waiting_input(istream &infile)
{
	string shopper = "";

	string arrival_s = "";
	string items_s = "";
	int id = 1;
	int arrival = 0;
	int items = 0;

	while(getline(infile, shopper))
	{
		int i = 0;
    	while(shopper[i] != ' ')
    	{
    		arrival_s+= shopper[i];
    		i++;
    	}
    	arrival = stoi(arrival_s);
    	i++;
    	while(i < (int) shopper.size())
    	{
    		items_s += shopper[i];
    		i++;
    	}
    	items = stoi(items_s);

    	Shopper s;
    	s.id = id;
    	s.arrival_time = arrival;
    	s.num_items = items;
    	s.items_left = items;
    	waiting.enqueue(s);

    	id++;
    	arrival_s = "";
    	items_s = "";
	}
}

// Function: processing
// Input: Nothing
// Returns: Nothing
// Does: Processing one item of the first shopper in each lane,
//    	 separating those in standard lanes and express lanes
//    	 if shopper is finished(item_left == 0), print info of shopper
void GrocerySim::processing()
{
  	for(int i = 0; i < num_standard_lanes; i++)
	{

       	lanes[i].front().items_left--;
       	if (lanes[i].front().items_left == 0)
        {        		
            cout << "Shopper " << lanes[i].front().id << " arrived at ";
            cout << lanes[i].front().arrival_time << " with ";
            cout << lanes[i].front().num_items << " items, took ";
            cout << (time - lanes[i].front().arrival_time) << " units";
            cout << endl;
            lanes[i].dequeue();
        }
    }
    
    for(int i = 0; i < num_express_lanes; i++)
	{

		if(express[i].isEmpty() == false)
		{
       		express[i].front().items_left--;

	       	if (express[i].front().items_left == 0)
	        {        		
	            cout << "Shopper " << express[i].front().id << " arrived at ";
	            cout << express[i].front().arrival_time << " with ";
	            cout << express[i].front().num_items << " items, took ";
	            cout << (time - express[i].front().arrival_time) << " units";
	            cout << endl;
	            express[i].dequeue();
	        }
	    }
    }
}

// Function: distributing
// Input: Nothing
// Returns: Nothing
// Does: Distributing any new shoppers in line,
//       A shopper goes in the express lane only if the number of items 
//       of a new shopper is less than or equal to the max number of express
void GrocerySim::distributing()
{

	if(waiting.size() != 0)
	{
		if(waiting.front().arrival_time == time)
	    {
	    	int least_total;
	    	int least_total_index = 0;
	    	if(waiting.front().num_items <= max_express_items)
	    	{
	    		least_total = express[0].totalItems();
	    		for(int i = 1; i < num_express_lanes; i++)
	    		{
	    			if (express[i].totalItems() < least_total)
	    			{
	    				least_total = express[i].totalItems();
	    				least_total_index = i;
	    			}
	    		}
	    		express[least_total_index].enqueue(waiting.front());
	    	}
	    	
	    	else
	    	{
	    		least_total = lanes[0].totalItems();
	    		for(int i = 1; i < num_standard_lanes; i++)
	    		{
	    			if (lanes[i].totalItems() < least_total)
	    			{
	    				least_total = lanes[i].totalItems();
	    				least_total_index = i;
	    			}
	    		}
	    		lanes[least_total_index].enqueue(waiting.front());
	    	}
	    	waiting.dequeue();
	    }
	}    	
}

// Function: distributing
// Input: Nothing
// Returns: Nothing
// Does: Checking if all lanes are empty
bool GrocerySim::empty_check()
{
	for(int i = 0; i < num_standard_lanes; i++)
    {
    	if(lanes[i].isEmpty() == false)
  		{
    		return false;
  		}
    }

    for(int i = 0; i < num_express_lanes; i++)
    {
    	if(express[i].isEmpty() == false)
    	{
    		return false;
    	}
    }

    return true;
}

// Function: Run
// Input: istread object
// Returns: Nothing
// Does: Simulates a grocery store with shoppers, stops when none are left
//		 Uses many helper functions, and accesses time to keep track.
void GrocerySim::run(istream &infile)
{	
	//variables for simulation
	time = 0;
	bool empty = false;
	CheckoutQueue lanes [num_standard_lanes];
	CheckoutQueue express [num_express_lanes];

	waiting_input(infile);
	waiting.print();

    while (empty == false)
    {

    	if(empty_check() == false)
    	{
    		processing();
    	}


    	distributing();


    	if((time > 1) && (empty_check() == true))
    	{
    		empty = true;
    	}

    	//incrementing time
    	time++;
    }
}




// Insert any private functions below this line