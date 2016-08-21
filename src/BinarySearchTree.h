#ifndef BINARYSEARCHTREE_H_INCLUDED
#define BINARYSEARCHTREE_H_INCLUDED

#include <algorithm>
#include <iostream>




template <typename Object>
class BinarySearchTree
{
private:
    struct BinaryNode
    {
        Object element;
        BinaryNode* left;
        BinaryNode* right;


        BinaryNode( const Object &theElement , BinaryNode* lt , BinaryNode* rt ): element{ theElement } , left{ lt } , right{ rt } {}

        BinaryNode( const Object &&theElement , BinaryNode* lt , BinaryNode* rt ): element{ std::move(theElement) } , left{ lt } , right{ rt } {}
    };

    BinaryNode* root;

   /**
    *   Internal method to insert into a subtree
    *   x is the item to insert
    *   t is the node that roots the subtree
    *   Set the new root of the subtree
    */
    void insert( const Object &x , BinaryNode* &t )
    {
        if( t == nullptr) {
            t = new BinaryNode{ x , nullptr , nullptr };
        }
        else if( x < t->element ) {
            insert( x , t->left );
        }
        else if( t->element < x ) {
            insert( x , t->right );
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
    void insert( const Object &&x , BinaryNode* &t )
    {
        if( t == nullptr) {
            t = new BinaryNode{ std::move( x ) , nullptr , nullptr };
        }
        else if( x < t->element ) {
            insert( std::move( x ) , t->left );
        }
        else if( t->element < x ) {
            insert( std::move( x ) , t->right );
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
    void remove( const Object &x , BinaryNode* &t )
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
            BinaryNode* oldNode = t;
            t = ( t->left != nullptr ) ? t->left : t->right;
            delete oldNode;
        }
    }

   /**
    *   Internal method to find the smallest item in a subtree t.
    *   Return node containing the smallest item.
    */
    BinaryNode* findMin( BinaryNode* t ) const
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
    BinaryNode* findMax( BinaryNode* t ) const
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
    bool contains( const Object & x , BinaryNode* t ) const
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
    void makeEmpty( BinaryNode* t )
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
    BinaryNode* clone( BinaryNode* t ) const
    {
        if( t != nullptr ) {
            return new BinaryNode { t->element , clone( t->left ) , clone( t->right ) };
        }

        return nullptr;
    }

   /**
    *   Internal method to print a subtree rooted at t in sorted order.
    */
    void printTree( BinaryNode* t , std::ostream &out ) const
    {
        if( t != nullptr ) {
            printTree( t->left , out );
            out << t->element << std::endl;
            printTree( t->right , out );
        }
    }



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
        insert( x , root );
    }

   /**
    *   Insert x into the tree; duplicates are ignored.
    */
    void insert( const Object &&x )
    {
        insert( std::move( x ) , root );
    }

   /**
    *   Remove x from the tree. Nothing is done if x is not found.
    */
    void remove( const Object &x )
    {
        remove( x , root );
    }
};

#endif // BINARYSEARCHTREE_H_INCLUDED
