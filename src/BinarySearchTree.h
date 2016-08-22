#ifndef BINARYSEARCHTREE_H_INCLUDED
#define BINARYSEARCHTREE_H_INCLUDED

#include <algorithm>
#include <iostream>

#include "BinaryNode.h"

template <typename Object>
class BinarySearchTree
{
public:
    class BstIterator: public std::iterator<std::bidirectional_iterator_tag , Object>
    {
    public:
        typedef Object value_type;

        BstIterator(): nodePtr{ nullptr } , tree{ nullptr } {}

        // Comparison Operators. Just compare node pointers
        bool operator== ( const BstIterator &rhs ) const
        { return ( nodePtr == rhs.nodePtr && tree == rhs.tree ); }

        bool operator!= ( const BstIterator &rhs ) const
        { return ( nodePtr != rhs.nodePtr || tree != rhs.tree ); }

        // Dereference Operator. Return a reference to the value
        // Pointed to by nodePtr
        const Object & operator* () const
        {
            if( nodePtr == nullptr ) {
                // throw UnderFlowException{};
            }
            return nodePtr->element;
        }

        // Pre-increment. Move forward to next larger value
        BstIterator & operator++ ()
        {
            BinaryNode<Object>* p;

            if ( nodePtr == nullptr )
            {
                // ++ from end(). get the root of the tree
                nodePtr = tree->root;

                // error! ++ requested for an empty tree
                if ( nodePtr == nullptr )
                    //throw UnderflowException { };

                // move to the smallest value in the tree,
                // which is the first node in-order
                while ( nodePtr->left != nullptr ) {
                    nodePtr = nodePtr->left;
                }
            }
            else if ( nodePtr->right != nullptr )
            {
                // successor is the farthest left node of
                // right subtree
                nodePtr = nodePtr->right;

                while ( nodePtr->left != nullptr ) {
                    nodePtr = nodePtr->left;
                }
            }
            else
            {
                // Have already processed the left subtree, and
                // there is no right subtree. move up the tree,
                // looking for a parent for which nodePtr is a left child,
                // stopping if the parent becomes NULL. a non-NULL parent
                // is the successor. if parent is NULL, the original node
                // was the last node inorder, and its successor
                // is the end of the list
                p = nodePtr->parent;
                while ( p != nullptr && nodePtr == p->right )
                {
                    nodePtr = p;
                    p = p->parent;
                }

                // if we were previously at the right-most node in
                // the tree, nodePtr = nullptr, and the iterator specifies
                // the end of the list
                nodePtr = p;
            }

            return *this;
        }

        // Post-increment
        BstIterator operator++ ( int )
        {
            BstIterator old = *this;
            ++ ( *this );
            return old;
        }

        // Pre-decrement. Move backward to largest value < current value
        BstIterator operator-- ()
        {
            BinaryNode<Object>* p;

            // Node is pointing to end()
            if( nodePtr == nullptr )
            {
                // Point to the root of the tree
                nodePtr = tree->root;

                // Node is empty
                if( nodePtr == nullptr ) {
                    // throw UnderflowException{};
                }

                // Start from root and move to the rightmost node
                while( nodePtr->right != nullptr ) {
                    nodePtr = nodePtr->right;
                }
            }
            else if( nodePtr->left != nullptr ) {

                nodePtr = nodePtr->left;

                while( nodePtr->right != nullptr ) {
                    nodePtr = nodePtr->right;
                }
            }
            else {
                p = nodePtr->parent;

                while( p != nullptr && nodePtr == p->left ) {
                    nodePtr = p;
                    p = p->parent;
                }

                nodePtr = p;
            }

            return *this;
        }

        // Post-decrement
        BstIterator operator-- ( int )
        {
            auto old = *this;
            operator--();
            return old;
        }

    private:
        friend class BinarySearchTree;

        // nodePtr is the current location in the tree. we can move
        // freely about the tree using left, right, and parent.
        // tree is the address of the tree object associated
        // with this iterator. it is used only to access the
        // root pointer, which is needed for ++ and --
        // when the iterator value is end()
        const BinaryNode<Object>* nodePtr;
        const BinarySearchTree* tree;

        // Used to construct an iterator return value from a node pointer
        BstIterator( const BinaryNode<Object>* p , const BinarySearchTree* t ): nodePtr{ p } , tree{ t } {}
    };

public:
    typedef BstIterator const_iterator;
    typedef const_iterator iterator;

   /**
    *   Search for an item. If found, return an iterator pointing
    *   at it in the tree; otherwise return end()
    */
    const_iterator find( const Object &item ) const
    {
        auto t = root;

        while( t != nullptr && t->element != item ) {
            t = ( item < t->item ) ? t->left : t->right;
        }

        return BstIterator{ t , this };
    }

   /**
    *   Return an iterator pointing just past the end of the tree
    *   data
    */
    const_iterator begin() const
    { return const_iterator{ findMin(root) , this }; }

   /**
    *   Return an iterator pointing to the first item( In-Order )
    */
    const_iterator end() const
    { return const_iterator{ nullptr , this }; }

public:
    BinarySearchTree(): root{ nullptr } {}

   /**
    *   Copy Constructor
    */
    BinarySearchTree( const BinarySearchTree &rhs ): root{ nullptr }
    {
        root = clone( rhs.root );
    }

   /**
    *   Move Constructor
    */
    BinarySearchTree( BinarySearchTree &&rhs ): root{ rhs.root }
    {
        rhs.root = nullptr;
    }

   /**
    *   Destructor for Tree
    */
    ~BinarySearchTree()
    {
        makeEmpty();
    }

   /**
    *   Copy Assignment
    */
    BinarySearchTree & operator= ( const BinarySearchTree &rhs )
    {
        BinarySearchTree copy = rhs;
        std::swap( *this , copy );
        return *this;
    }

   /**
    *   Move Assignment
    */
    BinarySearchTree & operator= ( const BinarySearchTree &&rhs )
    {
        std::swap( root , rhs.root );
        return *this;
    }

   /**
    *   Find the smallest item in the tree
    *   Throw underflow exception if empty
    */
    const Object & findMin() const
    {
        if( isEmpty() ) {
            //throw UnderflowException{};
        }

        return findMin( root )->element;
    }

   /**
    *   Find the largest item in the tree.
    *   Throw UnderflowException if empty.
    */
    const Object & findMax() const
    {
        if( isEmpty() ) {
            //throw UnderflowException{};
        }

        return findMax( root )->element;
    }

   /**
    *   Returns true if x is found in the tree.
    */
    bool contains( const Object &x ) const
    {
        return contains( x , root );
    }

   /**
    *   Test if the tree is logically empty.
    *   Return true if empty, false otherwise.
    */
    bool isEmpty() const
    {
        return root == nullptr;
    }

   /**
    *   Print the tree contents in sorted order.
    */
    void printTree( std::ostream &out = std::cout ) const
    {
        if( isEmpty() ) {
            out << "Empty Tree" << std::endl;
        }
        else {
            printTree( root , out );
        }
    }

   /**
    *   Make the tree logically empty.
    */
    void makeEmpty()
    {
        makeEmpty( root );
    }

   /**
    *   Insert x into the tree; duplicates are ignored.
    */
    void insert( const Object &x )
    {
        insert( x , root , nullptr );
    }

   /**
    *   Insert x into the tree; duplicates are ignored.
    */
    void insert( const Object &&x )
    {
        insert( std::move( x ) , root , nullptr );
    }

   /**
    *   Remove x from the tree. Nothing is done if x is not found.
    */
    void remove( const Object &x )
    {
        remove( x , root );
    }

private:
    BinaryNode<Object>* root;

   /**
    *   Internal method to insert into a subtree
    *   x is the item to insert
    *   t is the node that roots the subtree
    *   Set the new root of the subtree
    */
    void insert( const Object &x , BinaryNode<Object>* &t , BinaryNode<Object>* par )
    {
        if( t == nullptr) {
            t = new BinaryNode<Object> { x , nullptr , nullptr , par };
        }
        else if( x < t->element ) {
            insert( x , t->left , t );
        }
        else if( t->element < x ) {
            insert( x , t->right , t );
        }
        else {
            ; //Duplicate - Do Nothing
        }
    }

   /**
    *   Internal method to insert into a subtree
    *   x is the item to insert
    *   t is the node that roots the subtree
    *   Set the new root of the subtree
    */
    void insert( const Object &&x , BinaryNode<Object>* &t , BinaryNode<Object>* par )
    {
        if( t == nullptr) {
            t = new BinaryNode<Object> { std::move( x ) , nullptr , nullptr , par };
        }
        else if( x < t->element ) {
            insert( std::move( x ) , t->left , t );
        }
        else if( t->element < x ) {
            insert( std::move( x ) , t->right , t );
        }
        else {
            ; // Duplicate - Do Nothing
        }
    }

   /**
    *   Internal method to remove from a subtree.
    *   x is the item to remove.
    *   t is the node that roots the subtree.
    *   Set the new root of the subtree.
    */
    void remove( const Object &x , BinaryNode<Object>* &t )
    {
        if( t == nullptr ) {
            return; // Nothing is found. Return.
        }

        if( x < t->element ) {
            remove( x , t->left );
        }
        else if( t->element < x ) {
            remove( x , t->right );
        }
        else if( t->left != nullptr && t->right != nullptr ) { // Two Children
            t->element = findMin( t->right )->element;
            remove( t->element , t->right );
        }
        else {
            BinaryNode<Object>* oldNode = t;

            if( t->left == nullptr ) {
                t->right->parent = t->parent;
            }
            else {
                t->left->parent = t->parent;
            }

            t = ( t->left != nullptr ) ? t->left : t->right;

            delete oldNode;
        }
    }

   /**
    *   Internal method to find the smallest item in a subtree t.
    *   Return node containing the smallest item.
    */
    BinaryNode<Object>* findMin( BinaryNode<Object>* t ) const
    {
        if( t == nullptr ) {
            return nullptr;
        }
        if( t->left == nullptr ) {
            return t;
        }

        return findMin( t->left );
    }

   /**
    *   Internal method to find the largest item in a subtree t.
    *   Return node containing the largest item.
    */
    BinaryNode<Object>* findMax( BinaryNode<Object>* t ) const
    {
        if( t != nullptr ) {
            while( t->right != nullptr ) {
                t = t->right;
            }
        }

        return t;
    }

   /**
    *   Internal method to test if an item is in a subtree.
    *   x is item to search for.
    *   t is the node that roots the subtree.
    */
    bool contains( const Object &x , BinaryNode<Object>* t ) const
    {
        if( t == nullptr ) {
            return false;
        }
        else if( x < t->element ) {
            return contains( x , t->left );
        }
        else if( t->element < x ) {
            return contains( x , t->right );
        }
        else {
            return true;
        }
    }

/****** NONRECURSIVE VERSION*************************
    bool contains( const Comparable & x, BinaryNode *t ) const
    {
        while( t != nullptr )
            if( x < t->element )
                t = t->left;
            else if( t->element < x )
                t = t->right;
            else
                return true;    // Match

        return false;   // No match
    }
*****************************************************/

   /**
    *   Internal method to make subtree empty.
    */
    void makeEmpty( BinaryNode<Object>* t )
    {
        if( t != nullptr ) {
            makeEmpty( t->left );

            makeEmpty( t->right );

            delete t;
        }

        t = nullptr;
    }

   /**
    *   Internal method to clone subtree.
    */
    BinaryNode<Object>* clone( BinaryNode<Object>* t ) const
    {
        if( t != nullptr ) {
            return new BinaryNode<Object> { t->element , clone( t->left ) , clone( t->right ) , clone( t->parent ) };
        }

        return nullptr;
    }

   /**
    *   Internal method to print a subtree rooted at t in descending order.
    */
    void printTree( BinaryNode<Object>* t , std::ostream &out ) const
    {
        if( t != nullptr ) {
            printTree( t->right , out );
            out << t->element << std::endl;
            printTree( t->left , out );
        }
    }
};

#endif // BINARYSEARCHTREE_H_INCLUDED
