#include <iostream>
#include "BinarySearchTree.h"

int main()
{
    BinarySearchTree<int> bst{};

    int n , i = 0 , input;
    std::cin >> n;

    while( i++ < n ) {
        std::cin >> input;
        bst.insert( input );
    }

    for( auto iter = --bst.end() ; iter != bst.begin() ; iter -- ) {
        std::cout << *iter << std::endl;
    }

    std::cout << *bst.begin() << std::endl;
}
