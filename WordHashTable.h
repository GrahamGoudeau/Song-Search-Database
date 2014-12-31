#ifndef WORDHASHTABLE_H
#define WORDHASHTABLE_H

#include <iostream>
#include <vector>
#include "hashfunc.h"

struct Word_Node {
	std::string word;
	
	std::vector<std::string> title;
	std::vector<std::string> artist;
};

// Word_Vector_t is the new type for the table itself
typedef std::vector<std::vector<Word_Node> > Word_Vector_t;

const float WORD_LOAD_FACTOR = 0.7;


class WordHashTable {
public:
	WordHashTable();

	void add_word(std::string word, std::string artist, std::string title);
	bool contains_word(std::string word);
	Word_Node get_word(std::string search);

private:
	float population;
	int table_size;
	float load_factor;

	Word_Vector_t hash_table;

	int hash(std::string word);
	void expand_table();
};

#endif
