#include <iostream>
#include <string>
#include <cstdio>
#include <fstream>
#include "GrocerySim.h"

using namespace std;

int main()
{
	//initializing CheckoutQueue and shoppers
    CheckoutQueue lanes;

    Shopper s1;
    s1.id = 1;
    s1.arrival_time = 1;
    s1.num_items = 6;
    s1.items_left = 6;

    Shopper s2;
    s2.id = 2;
    s2.arrival_time = 2;
    s2.num_items = 12;
    s2.items_left = 12;

	Shopper s3;
    s3.id = 3;
    s3.arrival_time = 5;
    s3.num_items = 6;
    s3.items_left = 6;    

    //checking isEmpty and enqueue
    if(lanes.isEmpty() == true)
    {
    	cout << "The queue is empty" << endl;
    }

    lanes.enqueue(s1);
    lanes.enqueue(s2);
    lanes.enqueue(s3);

    if(lanes.isEmpty() == true)
    {
    	cout << "The queue is empty" << endl;
    }


    //checking size, totalItems, and dequeue
    cout << "The size of the queue is " << lanes.size() << endl;
    cout << "The total items in the lane are " << lanes.totalItems() << endl;
    lanes.dequeue();
    cout << lanes.size() << endl;

    cout << "The size of the queue is " << lanes.size() << endl;
    cout << "The total items in the lane are " << lanes.totalItems() << endl;

    //checking front
    cout << "Now, shopper number " << lanes.front().id << " is waiting at the front" << endl;


    return 0;

}