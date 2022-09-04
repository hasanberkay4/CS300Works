#ifndef _AVL_H
#define _AVL_H

#include "BST.h"

template <class Object>
        class AvlTree;

        template <class Object>
        class AvlNode
        {
               Object 	element;
               AvlNode   	*left;
               AvlNode   	*right;
			   int        	height;

               AvlNode( const Object & theElement, 
			              AvlNode *lt, AvlNode *rt, int h = 0 )
                    : element( theElement ), left( lt ), right( rt ), height( h ) { }

              friend class AvlTree<Object>;
        };

template <class Object>
class AvlTree
{
     public:
         explicit AvlTree( );
         AvlTree( const AvlTree & rhs );
	    ~AvlTree( );

        const AvlNode<Object>* & findMin( ) const;
        const AvlNode<Object>* & findMax( ) const;
        Object* find( const Object & x ) const;
        bool isEmpty( ) const;
        void printTree( ) const;

        void makeEmpty( );
        void insert( const Object & x );
        void remove( const Object & x );

	private:
		AvlNode<Object> *root;

        void insert( const Object & x, AvlNode<Object> * & t ) const;
        void remove(const Object & x, AvlNode<Object> * & t ) const;

        AvlNode<Object> * findMin( AvlNode<Object> *t ) const;
        AvlNode<Object> * findMax( AvlNode<Object> *t ) const;
        Object * find( const Object & x, AvlNode<Object> *t ) const;
        void makeEmpty( AvlNode<Object> * & t ) const;
        void printTree( AvlNode<Object> *t ) const;
        AvlNode<Object> * clone( AvlNode<Object> *t ) const;

        int height( AvlNode<Object> *t ) const;
        int max( int lhs, int rhs ) const;
        void rotateWithLeftChild( AvlNode<Object> * & k2 ) const;
        void rotateWithRightChild( AvlNode<Object> * & k1 ) const;
        void doubleWithLeftChild( AvlNode<Object> * & k3 ) const;
        void doubleWithRightChild( AvlNode<Object> * & k1 ) const;
};

struct AVLSection
{
	string title;
	AvlTree<item> items;
	AVLSection(){};
	AVLSection(string t): title(t){};

	friend bool operator > ( const AVLSection & x, const AVLSection & rhs)	{ return rhs.title < x.title; };
	friend bool operator < ( const AVLSection & x, const AVLSection & rhs)	{ return rhs.title > x.title; };
	friend bool operator == ( const AVLSection & x, const AVLSection & rhs)	{ return rhs.title == x.title; };

	friend ostream& operator << (ostream & os, const AVLSection & rhs) { os << rhs.title; return os; };
};

#endif