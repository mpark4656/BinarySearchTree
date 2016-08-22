#ifndef BINARYNODE_H_INCLUDED
#define BINARYNODE_H_INCLUDED

#include <algorithm>

template <typename Object>
struct BinaryNode
{
    Object element;
    BinaryNode* left;
    BinaryNode* right;
    BinaryNode* parent;


    BinaryNode( const Object &theElement , BinaryNode* lt , BinaryNode* rt , BinaryNode* par )
        : element{ theElement } , left{ lt } , right{ rt } , parent{ par } {}

    BinaryNode( const Object &&theElement , BinaryNode* lt , BinaryNode* rt , BinaryNode* par )
        : element{ std::move(theElement) } , left{ lt } , right{ rt } , parent{ par } {}
};

#endif // BINARYNODE_H_INCLUDED
