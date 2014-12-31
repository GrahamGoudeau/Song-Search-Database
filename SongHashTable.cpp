#include <iostream>
#include "SongHashTable.h"
#include "hashfunc.h"

using namespace std;


SongHashTable::SongHashTable() {
	population = 0;
	table_size = 20;

	hash_table.resize(table_size);
}

void SongHashTable::add_song(string artist, string title,
				string original_artist, string original_title) {
	int index = hash(artist, title);

	Song_Node new_song;
	new_song.hash_artist = artist;
	new_song.hash_title = title;
	new_song.artist = original_artist;
	new_song.title = original_title;

	// implements chaining in the hash table
	hash_table[index].push_back(new_song);

	population += 1;
	load_factor = population / table_size;

	if (load_factor >= SONG_LOAD_FACTOR) expand_table();	
}

void SongHashTable::add_lyrics(string title, 
			       string artist, 
			       vector<string> &lyrics) {

	int index = hash(artist, title);
	for (int i = 0; i < hash_table[index].size(); i++) {
		Song_Node cur = hash_table[index][i];

		// found the correct song to add lyrics to
		if (cur.hash_artist == artist && cur.hash_title == title) {
			for (int word = 0; word < lyrics.size(); word++) {
				string new_str = lyrics[word];
				hash_table[index][i].lyrics.push_back(new_str);
			}
		}
	}
}

Song_Node SongHashTable::get_song(string artist, string title) {
	uint32_t index = hash(artist, title);
	for (int i = 0; i < hash_table[index].size(); i++) {
		if (hash_table[index][i].hash_title == title && 
			hash_table[index][i].hash_artist == artist) {
			return hash_table[index][i];
		}
	}
	// used to suppress compiler warnings; 
	// the song is guaranteed to be in the table if this function is called
	return hash_table[0][0];
}


int SongHashTable::hash(string artist, string title) {
	string input = artist + title;
	uint32_t hash_code = hash_string(input);

	return hash_code % table_size; 
}

void SongHashTable::expand_table() {
	Song_Vector_t new_table;
	int new_size = table_size * 2;

	// updated table_size
	table_size = new_size;

	// make new_table the new size
	new_table.resize(new_size);

	// rehash and populate the new table
	for (int i = 0; i < hash_table.size(); i++) {
		for (int q = 0; q < hash_table[i].size(); q++) {
			Song_Node current = hash_table[i][q];
			string artist = current.hash_artist;
			string title = current.hash_title;
			int new_hash = hash(artist, title);
			new_table[new_hash].push_back(hash_table[i][q]);
		}
	}

	hash_table = new_table;
}

