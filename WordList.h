#ifndef WORDLIST_H
#define WORDLIST_H

#include <iostream>
#include "WordHashTable.h"
#include "SongHashTable.h"

class WordList {
public:
	void search();
	
	// read the lyrics from a file
	void read_lyrics(const char * filename, bool show_progress);

private:
	// convert a string to lowercase and without punctuation
	std::string alpha_only(std::string s);
	void print_context(std::vector<Song_Node> &songs, std::string word);
	void manage_print(Song_Node top_10[], std::string word);
	Song_Node find_song(Word_Node result, int song);

	WordHashTable hashtable_word;
	SongHashTable hashtable_song;
};
#endif
