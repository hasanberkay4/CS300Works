#include "Stack.h"

template <class Object>
Stack<Object>::Stack( )
{
        topOfStack = nullptr;
}

template <class Object>
bool Stack<Object>::isEmpty( ) const
{
        return topOfStack == nullptr;
}

template <class Object>
const Object & Stack<Object>::top( ) const
{
        if ( isEmpty( ) )
            cout << "Can not find top of empty stack!" << endl;
        return topOfStack->element;
}

template <class Object>
void Stack<Object>::push( const Object & x )
{
        topOfStack = new ListNode( x, topOfStack );
}

template <class Object>
void Stack<Object>::pop( )
{
        if ( isEmpty( ) )
            cout << "Can not pop empty stack!" << endl;
        ListNode *oldTop = topOfStack;
		topOfStack = topOfStack->next;
		delete oldTop;
}

template <class Object>
Object Stack<Object>::topAndPop( )
{
        Object topItem = top( );
        pop( );
        return topItem;
}

template <class Object>
void Stack<Object>::makeEmpty( )
{
    while ( ! isEmpty( ) )
            pop( );
}

template <class Object>
Stack<Object>::~Stack( )
{
        makeEmpty( );
}