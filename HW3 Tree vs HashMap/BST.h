#ifndef _BST_H
#define _BST_H

#include <string>
#include <iostream>

using namespace std;

template <class Object>
        class BinarySearchTree;


template <class Object>
class BinaryNode
{
    Object element;
    BinaryNode  *left;
    BinaryNode  *right;

    BinaryNode( const Object & theElement, 
		        BinaryNode *lt, BinaryNode *rt )
                : element( theElement ), left( lt ), right( rt ) { }
            
	friend class BinarySearchTree<Object>;
};

template <class Object>
class BinarySearchTree
{
    public:
		BinarySearchTree();
		 BinarySearchTree( const BinarySearchTree & rhs );
        ~BinarySearchTree( );
		
        const BinaryNode<Object> * & findMin( ) const;
        const BinaryNode<Object> * & findMax( ) const;

        Object * find( const Object & x ) const;
        void printTree( ) const;
		bool isEmpty( ) const;
        void makeEmpty( );

        void insert( const Object & x );
        void remove( const Object & x );
		BinaryNode<Object> * clone( BinaryNode<Object> *t ) const;
		void operator=( const BinarySearchTree & rhs );

	private:
        BinaryNode<Object> *root;

		BinaryNode<Object> * findMin( BinaryNode<Object> *t ) const;
		BinaryNode<Object> * findMax( BinaryNode<Object> *t ) const;

        void insert( const Object & x, BinaryNode<Object> * & t ) const;
        void remove( const Object & x, BinaryNode<Object> *& t ) const;
        Object * find( const Object & x, BinaryNode<Object> *t ) const;
        void makeEmpty( BinaryNode<Object> * & t ) const;
        void printTree( BinaryNode<Object> *t ) const;
};

struct item
{
	string title, info;
	item(){};
	item(string t, string i): title(t), info(i){};

	friend bool operator > ( const item & x, const item & rhs)	{ return rhs.title < x.title; };
	friend bool operator < ( const item & x, const item & rhs)	{ return rhs.title > x.title; };
	friend bool operator == ( const item & x, const item & rhs)	{ return rhs.title == x.title; };

	friend ostream& operator << (ostream & os, const item & rhs) { os << rhs.title; return os; };
};

#endif