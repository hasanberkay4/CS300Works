#include "BST.h"
#include <iostream>

using namespace std;

template <class Object>
BinarySearchTree<Object>::
BinarySearchTree() :
	root( nullptr )
{
}

template <class Object>
BinarySearchTree<Object>::
BinarySearchTree( const BinarySearchTree<Object> & rhs )
{ 
	root = clone(rhs.root);
}

template <class Object>
BinaryNode<Object> *
BinarySearchTree<Object>::
clone( BinaryNode<Object> * t ) const
{
    if ( t == nullptr )
        return nullptr;
    else
        return new BinaryNode<Object> 
			( t->element, 
				clone( t->left ), 
				clone( t->right ) );
}

template <class Object>
void BinarySearchTree<Object>::operator= (const BinarySearchTree<Object> & rhs) 
{
   root = clone(rhs.root);
}

template <class Object>
Object * BinarySearchTree<Object>::
find( const Object & x ) const
{
    return find( x, root );
}


template <class Object>
Object * 
BinarySearchTree<Object>::
find( const Object & x, BinaryNode<Object> * t ) const
{  
	if(t == nullptr)
		return nullptr;
    if (x > t->element)
		return find(x, t->right);
    else if (x < t->element)
        return find(x, t->left);
    else
        return &(t->element); 
}

template <class Object>
const BinaryNode<Object> * & BinarySearchTree<Object>::findMin( ) const
{
    return findMin( root );
}

template <class Object>
BinaryNode<Object> *
BinarySearchTree<Object>::
findMin( BinaryNode<Object> *t ) const
{
	if( t == nullptr )
		return nullptr;
	if( t->left == nullptr )
		return t;
	return findMin( t->left );
}

template <class Object>
const BinaryNode<Object> * & BinarySearchTree<Object>::findMax( ) const
{
    return findMax( root );
}

template <class Object>
BinaryNode<Object> *
BinarySearchTree<Object>::findMax( BinaryNode<Object> *t ) const
{
	if( t == nullptr )
		return nullptr;
	if( t->right == nullptr )
		return t;
	return findMax( t->right );
}

template <class Object>
void BinarySearchTree<Object>::insert( const Object & x )
{
    insert( x, root );
}

template <class Object>
bool BinarySearchTree<Object>::
isEmpty(  ) const
{
	return root == nullptr;
}

template <class Object>
void BinarySearchTree<Object>::
insert( const Object & x, BinaryNode<Object> * & t ) const
{
	if( t == nullptr )
		t = new BinaryNode<Object>( x, nullptr, nullptr );
	else if( x < t->element )
		insert( x, t->left ); 
	else if( t->element < x )
		insert( x, t->right );
	else
		; 
}

template <class Object>
void BinarySearchTree<Object>::remove( const Object & x )
{
       remove( x, root );
}

template <class Object>
void BinarySearchTree<Object>::
remove( const Object & x, BinaryNode<Object> *& t ) const
{
    if( t == nullptr )
        return;   
    if( x < t->element )
        remove( x, t->left );
    else if( t->element < x )
        remove( x, t->right );

	else if( t->left != nullptr && t->right != nullptr )
    {
        t->element = findMin( t->right )->element;
        remove( t->element, t->right );
    }
    else
    {
        BinaryNode<Object> *oldNode = t;
        t = ( t->left != nullptr ) ? t->left : t->right;
        delete oldNode;
    }
}         

template <class Object>
void BinarySearchTree<Object>::makeEmpty( )
{
        makeEmpty( root );
}

template <class Object>
void BinarySearchTree<Object>::
makeEmpty( BinaryNode<Object> * & t ) const
{
    if( t != nullptr )
    {
        makeEmpty( t->left );
        makeEmpty( t->right );
        delete t;
    }
    t = nullptr;
}

template <class Object>
void BinarySearchTree<Object>::printTree( ) const
{
    if( isEmpty( ) )
		return;
    else
        printTree( root );
}

template <class Object>
void BinarySearchTree<Object>::
printTree( BinaryNode<Object> *t ) const
{
	if ( t != nullptr )
	{
		printTree( t->left );
		cout << t->element << endl;
		printTree( t->right );
	}
}
       
template <class Object>
BinarySearchTree<Object>::~BinarySearchTree( )
{
	makeEmpty();
}