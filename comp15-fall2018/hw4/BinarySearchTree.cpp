/*
 * BinarySearchTree.cpp
 */

#include <iostream>
#include <climits>
#include <fstream>
#include <sstream>

#include "BinarySearchTree.h"

using namespace std;

//constructor
BinarySearchTree::BinarySearchTree()
{
    root = NULL;
}

//destructor
BinarySearchTree::~BinarySearchTree()
{
        // walk tree in post-order traversal and delete
        post_order_delete(root);
        root = NULL;   // not really necessary, since the tree is going 
                       // away, but might want to guard against someone
                       // using a pointer after deleting
}

// Function: post_order_delete
// Input: Node
// Returns: Nothing
// Does: Deletes entire tree in post order(left-right-root) with recursion
void BinarySearchTree::post_order_delete(Node *node)
{
        // TODO: students write code here
        // (hint: use a post-order traversal to remove all nodes)
    if(node == NULL)
    {
        return;
    }
    
    post_order_delete(node->left);
    post_order_delete(node->right);
    delete node;
}

// copy constructor
BinarySearchTree::BinarySearchTree(const BinarySearchTree &source)
{
    // use pre-order traversal to copy the tree
    root = pre_order_copy(source.root);
}

// assignment overload
BinarySearchTree &BinarySearchTree::operator= (const BinarySearchTree &source)
{
    // TODO: Students write code here
    // check for self-assignment

    if(this == &source)
    {
        return *this;
    }
    else
    {
        root = pre_order_copy(source.root);
        post_order_delete(root);
        pre_order_copy(source.root);
        return *this;
    }
}

// Function: pre_order_copy
// Input: Node
// Returns: Node
// Does: Copies a tree in pre order(root-left-right) with recursion
Node *BinarySearchTree::pre_order_copy(Node *node) const
{
    // TODO: Students write code here
    // (hint: use a pre-order traversal to copy details from the
    // node to a new_node)
    if (node == NULL)
        return NULL;

    Node *new_node = new Node();
    new_node->data = node->data;
    new_node->count = node->count;
    new_node->left = pre_order_copy(node->left);
    new_node->right = pre_order_copy(node->right);

    return new_node; 
}

// Function: find_min
// Input: Nothing(Node for helper)
// Returns: Integer value
// Does: Returns node with smallest data with recursion, uses helper
int BinarySearchTree::find_min() const
{
        if (root == NULL)
                return INT_MIN;
        return find_min(root)->data;
}

Node *BinarySearchTree::find_min(Node *node) const
{
    if(node->left == NULL)
    {
        return node;
    }

    else
    {
        return find_min(node->left);
    }
}

// Function: find_max
// Input: Nothing(Node for helper)
// Returns: Integer value
// Does: Returns node with largest data with recursion, uses helper
int BinarySearchTree::find_max() const
{
        if (root == NULL)
                return INT_MAX;
        return find_max(root)->data;
}

Node *BinarySearchTree::find_max(Node *node) const
{
    if(node->right == NULL)
    {
        return node;
    }

    else
    {
        return find_max(node->right);
    }
}

// Function: contains
// Input: int value(Node and int value in helper)
// Returns: bool value
// Does: contains() returns true if the value is in the tree,
//       false if it is not in the tree, uses helper(recursion)
bool BinarySearchTree::contains(int value) const
{
    return contains(root, value);
}

bool BinarySearchTree::contains(Node *node, int value) const
{
    if(node == NULL)
    {
        return false;
    }

    if(node->data == value)
    {
        return true;
    }   
    
    if(node->data < value)
    {
        return contains(node->right, value);
    }

    else
    {
        return contains(node->left, value);
    }
}

// Function: insert
// Input: int value(Node, parent, and int value in helper)
// Returns: Nothing
// Does: inserts the value into the Binary Search Tree.
        // If the value is already in the tree, the node's count
        // is incremented by 1(recursion)
void BinarySearchTree::insert(int value)
{
    insert(root, NULL, value);
}

void BinarySearchTree::insert(Node *node, Node *parent, int value)
{
    if(parent == NULL && node == NULL)
    {
        root = new Node;
        root->data = value;
        root->count = 1;
        root->left = NULL;
        root->right = NULL;
        return;
    }

    if(node == NULL)
    {
        node = new Node;
        node->data = value;
        node->count = 1;
        node->left = NULL;
        node->right = NULL;

        if(parent->data < value)
            parent->right = node;
        else
            parent->left = node;
        return; 
    }

    if(node->data == value)
    {
        node->count++;
        return;
    }   
    
    if(node->data < value)
    {
        return insert(node->right, node, value);
    }

    else
    {
        return insert(node->left, node, value);
    }
    
}

// Function: remove
// Input: int value(Node, parent, and int value in helper)
// Returns: bool
// Does: deletes node and returns true if found, false if not(recursion)
bool BinarySearchTree::remove(int value)
{
        return remove(root, NULL, value);
}

bool BinarySearchTree::remove(Node *node, Node *parent, int value)
{
    if(node == NULL)
        return false;

    if(node->data == value)
    {
        if(node->count > 1)
            node->count--;
        else
        {
            if(children_count(node) == 0)
            {
                if(parent->left == node)
                    parent->left = NULL;
                else
                    parent->right = NULL;
            }
            else
            {
                if(children_count(node) == 1)
                    remove_with_one_child(node, parent);
                else
                    remove_with_two_children(node->left, node, node);
            }
            
        }
        return true;
    }

    if(node->data < value)
        return remove(node->right, node, value);
    else
        return remove(node->left, node, value);
}

// Function: children_count
// Input: Node
// Returns: int value
// Does: return the number of children that node has
int BinarySearchTree::children_count(Node *node)
{
    int children = 2;
    if(node->left == NULL)
        children--;
    if(node->right == NULL)
        children--;
    return children;
}

// Function: remove_with_one_child
// Input: Two nodes: a current node and its parent(parent of root is just root)
// Returns: Nothing
// Does: Successfully removes a node with one child by using recursion
void BinarySearchTree::remove_with_one_child(Node *node, Node *p)
{
    if(node->left == NULL)
        p->right = node->right;
    else
        p->left = node->left;
}

// Function: remove_with_two_children
// Input: Three nodes: a current node, its parent, the node that we are deleting
// Returns: Nothing
// Does: Successfully removes a node with two children by using recursion
//       The original node is replaced by the maximum of the left subtree
void BinarySearchTree::remove_with_two_children(Node *node, Node *orig, Node *p)
{
    if(node->right == NULL)
    {
        orig->data = node->data;
        orig->count = node->count;
        if(node->left != NULL)
        {
            if(p->left == node)
                p->left = node->left;
            else
                p->right = node->left;
        }
        return;
    }

    return remove_with_two_children(node->right, orig, node);
}


// Function: tree_height
// Input: Nothing(Node in helper)
// Returns: int value
// Does: returns height of tree by using recursion for subtrees
int BinarySearchTree::tree_height() const
{
        return tree_height(root);
}

int BinarySearchTree::tree_height(Node *node) const
{
    if (node==NULL)  
       return -1;
    else 
    { 
        int l = tree_height(node->left); 
        int r = tree_height(node->right); 
  
        if (l > r)  
            return(l+1); 
        else 
            return(r+1); 
    } 
}

// returns the total number of nodes
int BinarySearchTree::node_count() const
{
        return node_count(root);
}


int BinarySearchTree::node_count(Node *node) const
{
    if(node == NULL)
        return 0;

    return node_count(node->left) + 1 + node_count(node->right);
}

// return the sum of all the node values (including duplicates)
int BinarySearchTree::count_total() const
{
    return count_total(root);
}

int BinarySearchTree::count_total(Node *node) const
{

    if(node == NULL)
    {
        return 0;
    }

    return count_total(node->left) + (node->data * node->count) 
        + count_total(node->right);
}

// use the printPretty helper to make the tree look nice
void BinarySearchTree::print_tree() const
{
        printPretty(root, 1, 0, std::cout);
}

Node *BinarySearchTree::find_parent(Node *node, Node *child) const
{
        if (node == NULL) return NULL;

        // if either the left or right is equal to the child,
        // we have found the parent
        if (node->left == child or node->right == child) {
                return node;
        }

        // Use the binary search tree invariant to walk the tree
        if (child->data > node->data) {
                return find_parent(node->right, child);
        } else {
                return find_parent(node->left, child);
        }
}
