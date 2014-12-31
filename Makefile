#
# Makefile for SongSearch, Assignment 6
#
CXX = clang++
FLAGS = -Wall -g3

songsearch: main.cpp hashfunc.cpp hashfunc.h WordList.cpp WordList.h\
		WordHashTable.h WordHashTable.cpp \
		SongHashTable.h SongHashTable.cpp 
	${CXX} ${FLAGS} -o songsearch main.cpp hashfunc.cpp WordList.cpp\
				WordHashTable.cpp SongHashTable.cpp 
	
clean:
	rm -f songsearch

provide_design:
	provide comp15 hw5_design songsearch_design.txt

provide:
	provide comp15 hw6 main.cpp hashfunc.cpp hashfunc.h WordList.cpp \
		WordList.h WordHashTable.h WordHashTable.cpp SongHashTable.h\
		SongHashTable.cpp Makefile ReadMe.md 

