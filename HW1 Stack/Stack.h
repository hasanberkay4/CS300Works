#ifndef _STACK_H
#define _STACK_H

template <class Object>
class Stack
{
    public:
		Stack( );
		~Stack( );

		bool isEmpty( ) const;
		const Object & top( ) const;
		void push( const Object & x );
		void pop( );
		Object topAndPop( );
		void makeEmpty( );
		
	private:
        struct ListNode
        {
            Object   element;
            ListNode *next;

            ListNode( const Object & theElement, ListNode * n = nullptr )
                            : element( theElement ), next( n ) { }
        };

        ListNode *topOfStack; 
};

#endif