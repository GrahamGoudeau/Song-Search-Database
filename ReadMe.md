# ReadMe for COMP 15 HW6
## Song Search 


HOMEWORK 6
AUTHOR: GRAHAM GOUDEAU
DATE: December 7, 2014

Goal of hw6:
	Use the various data structures we have learned in class to implement a 
	database that can store songs (with their title/artist and lyrics) and 
	then efficiently search the database.  A search for a word should
	produce the ten songs where the word occurs most frequently, and print
	the context (five words before/five words after) of the search result.

Data structure used:
	The main data structures are two hash tables: one for storing the
	individual words, and one for storing the songs and their lyrics.  To
	reduce the chance of collisions in the song hash table, songs are hashed
	based on the concatenation of their title and artist.  The words are 
	simply hashed based on the words themselves (lowercase, punctuation 
	stripped away).  The hash tables are vectors of vectors (each "bucket" 
	in the hash table is another vector).  This allows the size of a bucket
	to be accessed easily, as well as easier memory management.  This also
	allows collisions to be handled with the chaining technique.
	
Files provided:
* main.cpp
	* runs the main program
* hashfunc.cpp
	* contains the hash functions
* hashfunc.h
	* the interface for the hash functions (this and hashfunc.cpp provided
	  by instructor)
* WordList.cpp
	* handles the reading in of data and the searching
* WordList.h
	* interface for the data input and searching
* WordHashTable.cpp
	* Implementation of a hashtable for storing the words
* WordHashTable.h
	* Interface for the hash table responsible for storing the words
* SongHashTable.cpp
	* Implementation of a hashtable for storing the songs and lyrics
* SongHashTable.h
	* Interface for the hash table responsible for storing the songs 
	  and their associated lyrics
* ReadMe.md
	* program documentation 
* Makefile
	* used to compile the program

To compile:
	use the provided Makefile
