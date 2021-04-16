/*
 * CheckoutQueue.h
 * COMP15
 * Fall 2018
 *
 * Interface of the GrocerySim class
 *
 */

#ifndef GROCERYSIM_H
#define GROCERYSIM_H
#include <istream>
#include <string>
#include <cstdio>
#include "shopper.h"
#include "CheckoutQueue.h"

using namespace std;

class GrocerySim
{
public:
	GrocerySim();
	GrocerySim(int num_standard_queue, int num_express, int max_express);
	~GrocerySim();
	void run (istream &infile);
private:
	//attributes
	int num_standard_lanes;
	int num_express_lanes;
	int max_express_items;
	int time;

	//Checkout Arrays
	CheckoutQueue* lanes;
	CheckoutQueue* express;
	CheckoutQueue waiting;

	//helper functions for run
	void waiting_input(istream &infile);
	void processing();
	void distributing();
	bool empty_check();

};

#endif