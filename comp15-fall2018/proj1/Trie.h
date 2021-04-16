/*
 * Trie.h
 * COMP15
 * Fall 2018
 *
 * Interface of the Trie class
 *
 */

#include <string>
#include <iostream>

#ifndef TRIE_H
#define TRIE_H

using namespace std;

struct Node
{
    string character; // info(A,C,T,G) or combinations of those 4 if collapsed
    Node *children[4]; //pointers to nodes; children[0] for A, 
    				   //children[1] for C, children[2] for G, last for T
					   //children[i] == NULL if nothing is there

    bool EndofWord;	//if true, then a sequence ends at that node
};

class Trie
{
public:
	Trie();
	~Trie();
	void insert(string sequence);
	string query(string sequence);
	string remove(string sequence);

	bool contains(string sequence);
	void print_trie();

private:
	Node *root;
	string letters [4];

	// the following functions are private helper functions
    // for the public functions. This is to avoid exposing the
    // internals of the trie publicly, so we pass the root (and
    // other information in some cases) to the functions below
    // from the public functions.
	void insert(Node *node, string sequence);

	Node* MakingNode(Node *node, string sequence);
	string StringButHead(string sequence);

	string query(Node *node, string sequence, string prefix);

	string findingClosestMatch(Node *node);
	string findMin(string a, string b, string c, string d);
	int calculateMatch(string sequence, string closestMatch);

	string remove(Node *node, Node *parent, string sequence);

	bool contains(Node *node, string sequence);
	string addMultiple(string line, string character);
	bool HasChildren(Node *node);
	void removeNode(Node *node, Node *parent);

	void print_trie(Node *node, string sequence);
	
	void  post_order_delete(Node *node);

};

#endif