/*
 * CheckoutQueue.h
 * COMP15
 * Fall 2018
 *
 * Interface of the CheckoutQueue class
 *
 */

#ifndef CHECKOUTQUEUE_H
#define CHECKOUTQUEUE_H

#include "shopper.h"

class CheckoutQueue
{
public:
	CheckoutQueue();
	~CheckoutQueue();
	bool isEmpty();
	int size();
	int totalItems();
	void enqueue(Shopper);
	Shopper &front();
	void dequeue();
	void print();
private:
	//TODO: most likely you will need to add something here
	int length;

    struct NodeType
	{
   		Shopper info;
    	NodeType *next;
	};

 	NodeType *head;
    NodeType *back;
	
};

#endif