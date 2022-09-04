#include "AVL.h"
#include <iostream>

using namespace std;

template <class Object>
AvlTree<Object>::
AvlTree() :
	root( nullptr )
{
}

template <class Object>
AvlTree<Object>::
AvlTree( const AvlTree<Object> & rhs )
{ 
	root = clone(rhs.root);
}

template <class Object>
AvlNode<Object> *
AvlTree<Object>::
clone( AvlNode<Object> * t ) const
{
    if ( t == nullptr )
        return nullptr;
    else
        return new AvlNode<Object> 
			( t->element, 
				clone( t->left ), 
				clone( t->right ) );
}

template <class Object>
Object * AvlTree<Object>::
find( const Object & x ) const
{
        return find( x, root );
}

template <class Object>
Object * AvlTree<Object>::
find( const Object & x, AvlNode<Object> * t ) const
{
    if ( t == nullptr )
        return nullptr;
    else if( x < t->element )
        return find( x, t->left );
    else if( t->element < x )
        return find( x, t->right );
    else
		return &(t->element); 
}

template <class Object>
int AvlTree<Object>::height( AvlNode<Object> *t ) const
 {
	if (t == nullptr)
		return -1;
	
    return t->height;
}

template <class Object>
int AvlTree<Object>::max( int lhs, int rhs ) const
{
    if (lhs > rhs)
	    return lhs;

    return rhs;            
}

template <class Object>
const AvlNode<Object> * & AvlTree<Object>::findMin( ) const
{
     return findMin( root );
}

template <class Object>
AvlNode<Object>*
AvlTree<Object>::findMin( AvlNode<Object> *t ) const
{
    if( t == nullptr )
        return nullptr;
    if( t->left == nullptr )
        return t;
    return findMin( t->left );
}

template <class Object>
const AvlNode<Object>* & AvlTree<Object>::findMax( ) const
{
     return findMax( root );
}

template <class Object>
AvlNode<Object>*
AvlTree<Object>::findMax( AvlNode<Object> *t ) const
{
    if( t == nullptr)
		return nullptr;
	if( t->right == nullptr)
		return t;
	return findMax( t->right );
}

template <class Object>
void AvlTree<Object>::insert( const Object & x )
{
    insert( x, root );
}

template <class Object>
void AvlTree<Object>::insert
( const Object & x, AvlNode<Object> * & t ) const
{
    if ( t == nullptr )
        t = new AvlNode<Object>( x, nullptr, nullptr );

    else if ( x < t->element ) {
        insert( x, t->left );
    
        if ( height( t->left ) - height( t->right ) == 2 )
            if ( x < t->left->element )
                rotateWithLeftChild( t );
            else	
                doubleWithLeftChild( t );
    }

    else if( t->element < x )
    {   
        insert( x, t->right );
        if ( height( t->right ) - height( t->left ) == 2 )
            if ( t->right->element < x )
            rotateWithRightChild( t );
        else
            doubleWithRightChild( t );
    }
    else
        ;  

    t->height = max( height( t->left ), height( t->right ) ) + 1;
}

template <class Object>
void AvlTree<Object>::rotateWithLeftChild
( AvlNode<Object> * & k2 ) const
{
    AvlNode<Object> *k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
    k1->height = max( height( k1->left ), k2->height ) + 1;
    k2 = k1;
}

template <class Object>
void AvlTree<Object>::rotateWithRightChild
( AvlNode<Object> * & k1 ) const
{
    AvlNode<Object> *k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
    k2->height = max( height( k2->right ), k1->height ) + 1;
    k1 = k2;
}

template <class Object>
void AvlTree<Object>::doubleWithLeftChild
( AvlNode<Object> * & k3 ) const
{
    rotateWithRightChild( k3->left );
    rotateWithLeftChild( k3 );
}

template <class Object>
void AvlTree<Object>::doubleWithRightChild
( AvlNode<Object> * & k1 ) const
{
    rotateWithLeftChild( k1->right );
    rotateWithRightChild( k1 );
}

template <class Object>
bool AvlTree<Object>::
isEmpty(  ) const
{
	return root == nullptr;
}

template <class Object>
void AvlTree<Object>::printTree( ) const
{
    if( isEmpty( ) )
        return;
    else
        printTree( root );
}

template <class Object>
void AvlTree<Object>::
printTree( AvlNode<Object> * t ) const
{
    if ( t != nullptr )
    {
		printTree( t->left );
		cout << t->element << endl;
		printTree( t->right );
    }
}

template <class Object>
void AvlTree<Object>::remove( const Object & x )
{
        remove( x, root );
}

template <class Object>
void AvlTree<Object>::remove(const Object & x, AvlNode<Object> * & t ) const
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
        AvlNode<Object> *oldNode = t;
        t = ( t->left != nullptr ) ? t->left : t->right;
        delete oldNode;
    }

	
	if( t == nullptr){
		return;
	}

	t->height = max( height( t->left ), height( t->right ) ) + 1;
	
	if(height(t->left) - height(t->right) == 2){
		if(height(t->left->left) - height(t->left->right) >= 0){
			 rotateWithLeftChild( t );
		}

		else{
             doubleWithLeftChild( t );
		}
	}

	else if(height(t->right) - height(t->left) == 2){
		if(height(t->right->right) - height(t->right->left) >= 0){
			rotateWithRightChild( t );
		}
		else{
			doubleWithRightChild( t );
		}
	}  
}

template <class Object>
void AvlTree<Object>::makeEmpty( )
{
        makeEmpty( root );
}

template <class Object>
void AvlTree<Object>::
makeEmpty( AvlNode<Object> * & t ) const
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
AvlTree<Object>::~AvlTree( )
{
    makeEmpty( );
}
