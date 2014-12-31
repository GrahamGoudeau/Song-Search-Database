#include "WordHashTable.h"

#include <iostream>
using namespace std;

WordHashTable::WordHashTable() {
	table_size = 200;
	population = 0;
	hash_table.resize(table_size);
}


void WordHashTable::add_word(string word, string artist, string title) {
	int index = hash(word);

	// if this bucket is unpopulated, simply add to table
	if (hash_table[index].size() < 1) {
		Word_Node new_word;
		new_word.word = word;
		new_word.title.push_back(title);
		new_word.artist.push_back(artist);

		hash_table[hash(word)].push_back(new_word);

	}
	// else search the bucket
	else {
		bool found_word = false;
		for (int i = 0; i < hash_table[index].size(); i++) {
			if (hash_table[index][i].word == word) {
				found_word = true;
				hash_table[index][i].title.push_back(title);
				hash_table[index][i].artist.push_back(artist);
			}
		}
		// word not in bucket case
		if (!found_word) {
			Word_Node new_word;
			new_word.word = word;
			new_word.title.push_back(title);
			new_word.artist.push_back(artist);
			
			hash_table[index].push_back(new_word);
		}
	}

	population += 1;
	load_factor = population / table_size;
	
	if (load_factor >= WORD_LOAD_FACTOR) expand_table();
}


int WordHashTable::hash(std::string word) {
	uint32_t hashcode = hash_string(word);
	return hashcode % table_size;
}

void WordHashTable::expand_table() {
	Word_Vector_t new_table;
	int new_size = table_size * 2;

	// updated table_size
	table_size = new_size;

	// make new_table the new size
	new_table.resize(new_size);

	// rehash and populate the new table
	for (int i = 0; i < hash_table.size(); i++) {
		for (int q = 0; q < hash_table[i].size(); q++) {
			int new_hash = hash(hash_table[i][q].word);
			new_table[new_hash].push_back(hash_table[i][q]);
		}
	}

	hash_table = new_table;
}

bool WordHashTable::contains_word(string word) {
	int index = hash(word);
	for (int i = 0; i < hash_table[index].size(); i++)
		if (hash_table[index][i].word == word) return true;

	return false;
}

Word_Node WordHashTable::get_word(string word) {
	int hash_value = hash(word);
	for (int i = 0; i < hash_table[hash_value].size(); i++) {
		if (hash_table[hash_value][i].word == word)
			return hash_table[hash_value][i];
	}

	// error case to suppress compiler warnings;
	// the table should be checked with contains_word()
	// before using this function
	return hash_table[0][0];
}
