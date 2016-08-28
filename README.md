# BinarySearchTree

Practice Creating Binary Search Tree ADT

BinarySearchTree class template

Creates a binary search tree for <Object>

CONSTRUCTION: Zero Parameter

Object must provide its own operator< if necessary.

******************PUBLIC OPERATIONS*********************

void insert( x )       --> Insert x

void remove( x )       --> Remove x

bool contains( x )     --> Return true if x is present

Comparable findMin( )  --> Return smallest item

Comparable findMax( )  --> Return largest item

boolean isEmpty( )     --> Return true if empty; else false

void makeEmpty( )      --> Remove all items


******************UPDATE 8/21/2016******************

Added BstIterator ADT and implemented the following public functions

begin(); --> Iterator pointing to the first element in the tree (leftmost item)

end(); --> Iterator pointing to the position just past the last element (Always nullptr)

find( x ); --> Returns iterator pointing to the position that x is found

operator++ --> Increment Iterator, pointing to the next position in the tree (In-Order Traversal). Provides both prefix and postfix

operator-- --> Decrement Iterator, pointing to the previous position (In-Order Traversal). Provides both prefix and postfix
