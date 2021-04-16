#include <iostream>
#include "BinarySearchTree.h"

using namespace std;

void print_tree_details(BinarySearchTree &bst)
{
    bst.print_tree();
    cout << "\n";
    cout << "min: "         << bst.find_min()    << "\n";
    cout << "max: "         << bst.find_max()    << "\n";
    cout << "nodes: "       << bst.node_count()  << "\n";
    cout << "count total: " << bst.count_total() << "\n";
    cout << "tree height: " << bst.tree_height() << "\n";
    cout << "\n";
}



int main()
{
	BinarySearchTree bst;
    int values[]  = {4, 2, 11, 15, 9, 1, -6, 5, 3, 15, 2, 5, 13, 14};
    int numValues = sizeof(values) / sizeof(int);

    
    for (int i = 0; i < numValues; i++)
    {
        bst.insert(values[i]);
    }
    if(bst.contains(2) == true)
    	cout << "It's a 2" << endl;
    if(bst.contains(100) == true)
    	cout << "It's a 100" << endl;

   print_tree_details(bst);

   bst.remove(3);
   bst.remove(2);
   bst.remove(1);
   bst.remove(11);

   print_tree_details(bst);



	return 0;
}