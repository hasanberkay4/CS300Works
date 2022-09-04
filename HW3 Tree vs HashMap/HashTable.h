#ifndef _HASHTABLE_H
#define _HASHTABLE_H

#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

template <class HashedObj>
class HashTable
{
	public:
        explicit HashTable( int size = 101 );
        HashTable( const HashTable & rhs )
                :  arr( rhs.arr ) {}

		HashedObj* find( const HashedObj & x );
		void makeEmpty( );

		void printStat(const int & prevSize);
		void printFinalStat();

        void insert( const HashedObj & x );
        void remove( const HashedObj & x );

        enum EntryType { ACTIVE, EMPTY, DELETED };

	private:
		struct HashEntry
		{
			 HashedObj element;
			 EntryType info;

			 HashEntry( const HashedObj & e = HashedObj( ), 
						EntryType i = EMPTY )
					  : element( e ), info( i ) { }
		};
            
		vector<HashEntry> arr;
		int currentSize;

		bool isActive( int currentPos ) const;
		int findPos( const HashedObj & x ) const;
		void rehash( );
};

inline bool isPrime(const int & n){
	for(int i = 2; i < sqrt(n); i++){
		if(n % i == 0){
			return false;
		}
	}
	return true;
}

inline int nextPrime( int n )
{
        if ( n % 2 == 0 )
            n++;

        for ( ; !isPrime( n ); n += 2 );

        return n;
}
/*
inline int hashF(const string & word, int tSize){
	int result = 0;
	
	cout << word << endl;
	for(int i = 0; i <  word.length(); i++)
		result = result * 37 + word[i];

		
	result = result % tSize;

	if(result < 0)
		result += tSize;

	return result;
}
*/

inline int hashF (const string & word, int tSize)
{	
	int result = 0;
  
    for (unsigned int i = 0; i < word.length(); i++)
	  result = 37 * result + word[i];

    result %= tSize;

    if (result < 0) 
	  result += tSize;

    return(result);
}

/*
inline int hashS (const int & word, int tSize)
{	
	int primeNum = tSize - 1;

	while(!isPrime(primeNum))
		primeNum--;

	return primeNum - (word % primeNum);
}
*/

#endif