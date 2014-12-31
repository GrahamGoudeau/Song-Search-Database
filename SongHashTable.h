#ifndef SONGHASHTABLE_H
#define SONGHASHTABLE_H

#include <iostream>
#include <vector>

struct Song_Node {
	std::string hash_artist;
	std::string hash_title;

	std::string artist;
	std::string title;

	std::vector<std::string> lyrics;
};

// Song_Vector_t is the new type of the hash table (vectors of vecors)
typedef std::vector<std::vector<Song_Node> > Song_Vector_t;

const float SONG_LOAD_FACTOR = 0.7;

class SongHashTable {
public:
	SongHashTable();

	void add_song(std::string artist, std::string title,
		      std::string original_artist, std::string original_title);
	void add_lyrics(std::string title, 
			std::string artist, 
			std::vector<std::string> &lyrics);

	bool contains_song(std::string artist, std::string title);
	Song_Node get_song(std::string artist, std::string title);

private:
	float population;
	int table_size;
	float load_factor;

	Song_Vector_t hash_table;

	int hash(std::string artist, std::string title);
	void expand_table();
};

#endif
