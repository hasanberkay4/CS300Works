#include "HashTable.h"
#include <iostream>
#include <cmath>

using namespace std;

template <class HashedObj>
void HashTable<HashedObj>::makeEmpty( )
{
    currentSize = 0;

    for(int i = 0; i < arr.size(); i++)
        arr[i].info = EMPTY;
}

template <class HashedObj>
HashTable<HashedObj>::HashTable( int size )
				: arr( nextPrime( size ) )
{
       makeEmpty( );
}

template <class HashedObj>
int HashTable<HashedObj>::findPos( const HashedObj & x ) const
{ 
    int collisionNum = 0;
    int currentPos = hashF( x.word, arr.size( ) );

    while ( arr[ currentPos ].info != EMPTY && 
		arr[ currentPos ].element != x )
    {
		currentPos += 2 * ++collisionNum - 1;
        // currentPos += pow(++collisionNum, 2) ; 
        if ( currentPos >= arr.size( ) )              
                currentPos = currentPos - arr.size( );                
    }   
    return currentPos;
            

    /*
    
    int collisionNum = 0;

    int currentPos = hashF(x.word[x.word.length() - 1], arr.size());

    int temp = hashS(currentPos, arr.size());

    while (arr.at(currentPos).info != EMPTY &&
        arr.at(currentPos).element != x)
    {
        //	currentPos = currentPos + collisionNum 2 * ++collisionNum - 1;
        //	currentPos += pow(++collisionNum, 2) ; 

        //currentPos += (++collisionNum * hashS(temp, arr.size())) % arr.size();
        //currentPos = (currentPos + ++collisionNum * temp) % arr.size();
    }

    return currentPos;

    */
    
}

template <class HashedObj>
bool HashTable<HashedObj>::isActive( int currentPos ) const
{
        return arr[ currentPos ].info == ACTIVE;
}

template <class HashedObj>
HashedObj* HashTable<HashedObj>::find( const HashedObj & x )
{
        int currentPos = findPos( x );
        if (arr[currentPos].info == ACTIVE) 
            return &(arr[currentPos].element); 
 
        return nullptr;
}

template <class HashedObj>
void HashTable<HashedObj>::printStat(const int & prevSize)
{
	cout << "rehashed..." << endl;

	cout << "previous table size: " << prevSize << ", new table size: "
		<< arr.size() << ", current unique word count: " << currentSize
		<< ", current load factor: " << float(currentSize) / arr.size() << endl;
}

template <class HashedObj>
void HashTable<HashedObj>::printFinalStat()
{
	cout << endl << "After preprocessing, the unique word count is " << currentSize 
		<< ". Current load ratio is " << float(currentSize) / arr.size() << endl << endl;
}

template <class HashedObj>
void HashTable<HashedObj>::insert( const HashedObj & x )
{
        // Insert x as active
        int currentPos = findPos( x );
        if ( isActive( currentPos ) )
            return;
        arr[ currentPos ] = HashEntry( x, ACTIVE );

        // enlarge the hash table if necessary 
	if ( ++currentSize >= arr.size( ) / 1.4)
        rehash( );
}

template <class HashedObj>
void HashTable<HashedObj>::remove( const HashedObj & x )
{
        int currentPos = findPos( x );
        if ( isActive( currentPos ) )
            arr[ currentPos ].info = DELETED;
}

template <class HashedObj>
void HashTable<HashedObj>::rehash( )
{
    vector<HashEntry> oldArray = arr;

    arr.resize( nextPrime( 2 * oldArray.size( ) ) );
    for (unsigned int j = 0; j < arr.size( ); j++ )
            arr[ j ].info = EMPTY;

    currentSize = 0;
    for ( int i = 0; i < oldArray.size( ); i++ )
        if ( oldArray[ i ].info == ACTIVE )
                insert( oldArray[ i ].element );
	
	printStat(oldArray.size());
}