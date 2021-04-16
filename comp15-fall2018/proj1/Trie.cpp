/*
 * BinarySearchTree.cpp
 */

#include <iostream>
#include <string>
#include <climits>
#include <fstream>
#include <sstream>
#include <math.h>

#include "Trie.h"

using namespace std;

//constructor
Trie::Trie()
{
    root = NULL;

    letters[0] = "A";
    letters[1] = "C";
    letters[2] = "G";
    letters[3] = "T";
}

//destructor
Trie::~Trie()
{
        // walk tree in post-order traversal and delete
        post_order_delete(root);
        root = NULL;
}

// Function: post_order_delete
// Input: Node
// Returns: Nothing
// Does: Deletes entire trie in post order(children, then root) with recursion
void Trie::post_order_delete(Node *node)
{
    if(node == NULL)
    {
        return;
    }

    for(int i = 0; i < 4; i++)
        post_order_delete(node->children[i]);
    delete node;
}



// Function: insert
// Input: string(Node and string in helper)
// Returns: Nothing
// Does: inserts the value into the Trie.
void Trie::insert(string sequence)
{
    insert(root, sequence);
}

// Function: insert
// Input: Node and string
// Returns: Nothing
// Does: inserts the value into the Trie using recursion
//       if node equals NULL(it is empty), it initialized the root
//       it returns once the sequence is empty(no more characters to insert)
//       accounts for ?'s
void Trie::insert(Node *node, string sequence)
{
    if(node == NULL){
        node = MakingNode(node, "");
        root = node;
    }

    if(sequence.size() == 0)
        return;
    //for question marks
    if(sequence.substr(0,1).compare("?") == 0)
        for(int i = 0; i < 4; i++)
            insert(node, letters[i] + StringButHead(sequence));
    else
    {
        for(int i = 0; i < 4; i++)
        {
            if(sequence.substr(0,1).compare(letters[i]) == 0){
                if(node->children[i] == NULL){
                    node->children[i] = new Node;
                    node->children[i]->character = letters[i];
                    for(int j = 0; j < 4; j++)
                        node->children[i]->children[j] = NULL;
                    node->children[i]->EndofWord = false;
                }
                //checking to see if we are at the end of the sequence
                if(sequence.size() == 1)
                    node->children[i]->EndofWord = true;
                //returns the new sequence, specific child
                return insert(node->children[i], StringButHead(sequence));
            }
        }
    }   
}

// Function: MakingNode
// Input: Node, string
// Returns: Node
// Does: returns an initialized node(for the root)
Node* Trie::MakingNode(Node *node, string sequence)
{
    node = new Node;
    node->character = sequence;
    for(int i = 0; i < 4; i++)
    {
        node->children[i] = NULL;
    }
    node->EndofWord = false;
    return node;
}

// Function: StringButHead
// Input: string
// Returns: string
// Does: returns the inputted string minus the first character
//       Example: StringButHead("Hello") returns "ello"
string Trie::StringButHead(string s1)
{
    string s2 = "";
    for(int i = 1; i < s1.size(); i++)
        s2 += s1[i];
    return s2;
}

// Function: query
// Input: string(two nodes and string in helper)
// Returns: string
// Does: public function of query calls the private one
//       retrieves the closest match of sequence and calculates the percentage
//       of similarity
//       accouts for matches not being found
string Trie::query(string sequence)
{
    string closestMatch = "";
    int percentage = 0;
    string percent_string = "";
    closestMatch = query(root, sequence, "");

    percentage = calculateMatch(sequence, closestMatch);
    if (percentage == 0)
    {
        return "No match found";
    }
    char perc[10];
    sprintf(perc , "%d" , percentage);
    percent_string = perc;
    return "Match found " + closestMatch + " " + percent_string + "%";
    
}

// Function: Query
// Input: Node, Node, string
// Returns: string
// Does: private helper function of query
//       retrieves the closest match of sequence by using recursion
//       calls findingClosestMatch when it reaches an uncommon prefix or end
string Trie::query(Node *node, string sequence, string prefix)
{
    if(node == NULL)
        return prefix;

    if((node->EndofWord == true) && (sequence.size() == 0))
        return prefix;

    if(sequence.size() == 0)
        return prefix + findingClosestMatch(node);
    for(int i = 0; i < 4; i++)
    {
        if(sequence.substr(0,1).compare(letters[i]) == 0)
        {
            if(node->children[i] != NULL)
            {
                return query(node->children[i], StringButHead(sequence),
                    prefix +=letters[i]);
            }
            else
            {
                if(prefix.size() == 0)
                    return "";
                else
                    return prefix + findingClosestMatch(node);
            }
        }                
    }
    return "";
}

// Function: findingClosestMatch
// Input: node
// Returns: string
// Does: returns the node with the smallest distance from a node that marks
//       the end of a word, uses findMin to compare branches
string Trie::findingClosestMatch(Node *node)
{
    if (node->EndofWord == true) 
    {
       return "";
    }

    else 
    { 
        string branches [4];
        for(int i = 0; i < 4; i++){
            if(node->children[i] != NULL)
                branches[i] =letters[i]+findingClosestMatch(node->children[i]);
            else
                branches[i] = "";
        }
        return(findMin(branches[0], branches[1], branches[2], branches[3]));
    } 
}

// Function: findMin
// Input: four strings
// Returns: string
// Does: returns the shortest string that isn't a null string
string Trie::findMin(string a, string b, string c, string d)
{
    string min = a;
    if((b.size() < min.size()) || (min.size() == 0))
        if(b.size() > 0)
            min = b;
    if((c.size() < min.size()) || (min.size() == 0))
        if(c.size() > 0)
            min = c;
    if((d.size() < min.size()) || (min.size() == 0))
        if(d.size() > 0)
            min = d;
    return min;
}

// Function: calculateMatch
// Input: two strings
// Returns: int
// Does: returns the percent of the common prefix / closestMatch
int Trie::calculateMatch(string sequence, string closestMatch)
{

    if(sequence.size() < closestMatch.size())
        return sequence.size() * 100 / closestMatch.size();
    if(sequence.size() > closestMatch.size())
        return closestMatch.size() * 100 / sequence.size();
    else
    {
        string prefix = "";
        for(int i = 0; i < sequence.size(); i++)
        {
            if(sequence[i] == closestMatch[i])
                prefix += sequence[i];
            else
                break;
        }
        return prefix.size() * 100 / closestMatch.size();
    }
}


// Function: remove
// Input: int value(Node, parent, and string in helper)
// Returns: string
// Does: removes sequence in the trie
//       if sequence is not found, it reports that it was not found
//       if sequence is found, it reports all the sequences removed
string Trie::remove(string sequence)
{
    if(!contains(sequence))
        return sequence + " not found ";
    else
        return remove(root, NULL, sequence);
    
}

// Function: remove
// Input: Node, parent, and string
// Returns: string
// Does: removes sequence in the trie by traversing the trie recursively
//       if it reaches the end of a word, it only deletes childless nodes
//       passes removed sequences on a string, takes care of multiple lines
//       works for question marks, not asterisks
string Trie::remove(Node *node, Node *parent, string sequence)
{    
    if((node->EndofWord == true) && (sequence.size() == 0)){
        if(!HasChildren(node))
            removeNode(node, parent);
        else
            node->EndofWord = false;
        return " removed\n";
    }

    if(sequence.size() == 0)
        return " not found\n";

    if(sequence.substr(0,1).compare("?") == 0){
        string question = "";
        for(int i = 0; i < 4; i++)
            if(node->children[i] != NULL)
                question += remove(node, parent,
                    letters[i] + StringButHead(sequence));
        return question;
    }

    for(int i = 0; i < 4; i++){
        if(sequence.substr(0,1).compare(letters[i]) == 0){
            string line = "";
            if(node->children[i] != NULL){
                line = sequence[0] + remove(node->children[i], node,
                    StringButHead(sequence));
                line = addMultiple(line, letters[i]);
                if(!HasChildren(node) && (node != root))
                    removeNode(node, parent);
                return line;
            }            
            return " not found\n";
        }         
    }
    return "";
}


// Function: addMultiple
// Input: two strings
// Returns: string
// Does: Adds the second string to all of the first string's lines
string Trie::addMultiple(string line, string character)
{
    for(int i = 0; i < line.size(); i++)
    {
        string temp = "";
        if((line.substr(i,1).compare("d") == 0) && (i != line.size() - 2))
        {
            temp = line.substr(0,i+2);
            temp += character;
            temp += line.substr(i+2,(line.size() - i - 1));
            line = temp;
        }
    }
    return line;
}

// Function: contains
// Input: string(node, string in helper)
// Returns: bool
// Does: checks to see if the sequence is in the trie
bool Trie::contains(string sequence)
{
    return contains(root, sequence);
}

// Function: contains
// Input: Node, string
// Returns: bool
// Does: checks to see if the sequence is in the trie
//       if sequence is not found, it returns false
//       if sequence is found, returns true
//       accoutns for question marks and asterisks
bool Trie::contains(Node *node, string sequence)
{
    if(node == NULL)
        return false;
    if((node->EndofWord == true) && (sequence.size() == 0))
        return true;
    if(sequence.size() == 0)
        return false;

    if(sequence.substr(0,1).compare("?") == 0){
        for(int i = 0; i < 4; i++){
            bool one = false;
            if(node->children[i] != NULL)
                one = contains(node, letters[i] + StringButHead(sequence));
            if(one)
                return one;
        }
        return false;
    }

    if(sequence.substr(0,1).compare("*") == 0){
        for(int i = 0; i < 4; i++)
            if(node->children[i] != NULL)
                return true;
        return false;
    }

    for(int i = 0; i < 4; i++){
        if(sequence.substr(0,1).compare(letters[i]) == 0){
            if(node->children[i] == NULL)
                return false;
            else
                return contains(node->children[i], StringButHead(sequence));
        }                
    }
    return false;
}

// Function: HasChildren
// Input: Node
// Returns: bool
// Does: Returns true if node has any children, false otherwise
bool Trie::HasChildren(Node *node)
{
    for(int i = 0; i < 4; i++)
    {
        if(node->children[i] != NULL)
            return true;
    }

    return false;
}

// Function: removeNode
// Input: node, parent
// Returns: nothing
// Does: removes node by making the parent point to null and clearing space
void Trie::removeNode(Node *node, Node *parent)
{
    for(int i = 0; i < 4; i++)
        if(parent->children[i] == node)
        {
            parent->children[i] = NULL;
            post_order_delete(node);
        }
}

// Function: print_trie
// Input: nothing(node and string in helper)
// Returns: nothing
// Does: prints the words in the trie
void Trie::print_trie()
{
    return print_trie(root, "");
}

// Function: print_trie
// Input: node and string in helper
// Returns: nothing
// Does: prints the words in the trie by going through it recursively
//       prints all sequences to cerr
void Trie::print_trie(Node *node, string sequence)
{
    if(node == NULL)
    {
        return;
    }


    if(node->EndofWord == true)
    {
        cerr << sequence << endl;
    }


    for(int i = 0; i < 4; i++)
    {
        print_trie(node->children[i], sequence + letters[i]);
    }


    return; 

}


