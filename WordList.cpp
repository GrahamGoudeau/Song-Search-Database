#include "WordList.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
//#include "WordHashTable.h"

using namespace std;

//
// read_lyics 
//   purpose: read in song data from a disk file
//   arguments: the name of the file, bool to ask for progress status
//   returns: nothing
//   does: calls a function each time a word is found
//
void WordList::read_lyrics(const char * filename, bool show_progress)
{
        ifstream in(filename);			// creates an input stream
        int song_count = 0;			// for progress indicator
	string artist, title, word;
	// changes start here
	//WordHashTable hashtable_word;
	// -- While more data to read...
	while ( ! in.eof() ) 
	{
		// -- First line is the artist
		getline(in, artist);
		if (in.fail()) break;

		// -- Second line is the title
		getline(in, title);
		if (in.fail()) break;

		if ( show_progress )
		{
			song_count++;
			if (song_count % 10000 == 0) {
				cout << "At "       << song_count << 
					" Artist: " << artist     << 
					" Title:"   << title << endl;
			}
		}

		hashtable_song.add_song(alpha_only(artist), alpha_only(title),
					artist, title);
		vector<string> lyrics;
		// -- Then read all words until we hit the 
		// -- special <BREAK> token
		while ( in >> word && word != "<BREAK>" ){
			//
			// -- Found a word
			lyrics.push_back(word);
			string alpha = alpha_only(word);
			hashtable_word.add_word(alpha, artist, title);
		}
		// add lyrics to the song
		hashtable_song.add_lyrics(alpha_only(title), 
					  alpha_only(artist), 
					  lyrics);
		// -- Important: skip the newline left behind
		in.ignore();
	}
}

//
// alpha_only
//   purpose: converts a string to lowercase and alphabetic characters
//            only. E.g., "Bang!" becomes "bang"
//   arguments: a string
//   returns: the alpha-only string
//   does: converts the string
//
string WordList::alpha_only(string s){
        ostringstream ss;
        for (size_t i=0;i<s.length();i++) {
                if (isalnum(s[i])){
                        ss << (char)(tolower(s[i]));
                }
        }
        return ss.str();
}

void WordList::search() {
	string search_term;
	cin >> search_term;
	while (search_term != "<BREAK>") {
		string alpha_search = alpha_only(search_term);
		Word_Node result;
		vector<Song_Node> containing_songs;

		// build list of containing songs
		if (hashtable_word.contains_word(alpha_search)) {
			result = hashtable_word.get_word(alpha_search);
			string last_title = "";
			string last_artist = "";
			Song_Node song;
			for (int i = 0; i < result.title.size(); i++) {
				if (result.artist[i] != last_artist || 
				    result.title[i]  != last_title) {
					song = find_song(result, i);
					containing_songs.push_back(song);
				}
				last_title = result.title[i];
				last_artist = result.artist[i];	
			}

		}
		print_context(containing_songs, search_term);
		cout << "<END OF REPORT>\n";
		cin >> search_term;
	}
}

Song_Node WordList::find_song(Word_Node result, int song) {
	string artist = alpha_only(result.artist[song]);
	string title = alpha_only(result.title[song]);
	return hashtable_song.get_song(artist, title);
}

void WordList::print_context(vector<Song_Node> &songs, string word) {
	Song_Node top_10[10];
	int counts[10];
	for (int i = 0; i < 10; i++) counts[i] = 0;

	// find top 10 songs
	for (int cur = 0; cur < songs.size(); cur++) {
		int word_count = 0;
		for (int lyric = 0; lyric < songs[cur].lyrics.size(); lyric++) {
			string cur_lyric = alpha_only(songs[cur].lyrics[lyric]);
			if (cur_lyric == alpha_only(word))
				word_count++;
		}
		// sort list of top 10
		for (int i = 0; i < 10; i++) {
			if (word_count >= counts[i]) {
				for (int q = 9; q > i; q--) {
					top_10[q] = top_10[q-1];
					counts[q] = counts[q-1];
				}
				top_10[i] = songs[cur];
				counts[i] = word_count;
				break;
			}
		}
	}
	manage_print(top_10, word);
}

void WordList::manage_print(Song_Node top_10[], string word) {
	for (int song = 0; song < 10; song++) {
		Song_Node cur_song = top_10[song];
		int num_lyrics = cur_song.lyrics.size();
		for (int q = 0; q < num_lyrics ; q++) {
			// determine start location
			int start;
			if (q - 5 <= 0) start = 0;
			else start = q - 5;

			int end = q + 6;
			string cur_word = alpha_only(cur_song.lyrics[q]);
			string alpha_word = alpha_only(word);

			// print title/artist/context
			if (cur_word == alpha_word) {
				cout << "Title: " << cur_song.title << endl;
				cout << "Artist: " << cur_song.artist << endl;
				cout << "Context: ";
				for (int k = start; k >= 0 && k < q; k++)
					cout << cur_song.lyrics[k] << " ";
				for (int k = q; k < num_lyrics && k < end; k++)
					cout << cur_song.lyrics[k] << " ";
				cout << endl << endl; 
			}
			
		}	
	}
}
