/*
Author: Mohammad Islam
Course: CSCI 137
Instructor: Genady Maryash
Assingment: Project 2 Task C

Project 2 Task C: Music playlist
*/

#include <iostream>
#include <string>
#include <fstream>
using namespace std;


int g_capacity = 2;
int g_size = 0;

class Song {
    public:
        string name;
        string artist;
        int duration;
        string genre;
};

Song *g_songs = new Song[g_capacity];

void allocateNew()
{
    Song *fsongs = new Song[g_capacity * 2];

    for (int i = 0; i < g_capacity; i++) {
        fsongs[i] = g_songs[i]; 
    }

    delete [] g_songs;

    g_songs = fsongs;
    g_capacity = g_capacity * 2;
}

void readSongs(string filename)
{
    ifstream fin(filename);
    if (fin.fail()) {
    cerr << "File cannot be opened for reading." << endl;
    exit(1); // exit if failed to open the file
    }


    string line, song_name, artist_name, genre, duration_prelims, junk;
    int duration;

    getline(fin, song_name, ':');
    getline(fin, artist_name, '-');
    getline(fin, genre, '-');
    getline(fin, duration_prelims, ' ');
    duration = stoi(duration_prelims);

    g_songs[0].name = song_name; 
    g_songs[0].artist = artist_name;
    g_songs[0].genre = genre;
    g_songs[0].duration = duration;

    g_size = g_size + 1;

    while (getline(fin, line)) {

        if (g_capacity == g_size) {
            allocateNew();
        }

        getline(fin, song_name, ':');
        getline(fin, artist_name, '-');
        getline(fin, genre, '-');
        getline(fin, duration_prelims, ' ');

        duration = stoi(duration_prelims);

        g_songs[g_size].name = song_name;
        g_songs[g_size].artist = artist_name;
        g_songs[g_size].duration = duration;
        g_songs[g_size].genre = genre;

        g_size++;
    }
    
    g_size = g_size - 1;
}

Song * getGenreSongs(string genre, int &genreCount)
{
    Song * wanted = new Song[g_size];
    Song * nothing = new Song[g_size];
    genreCount = 0;
    int count = 0;
    int hi = 0;
    int ho = 0;
    for (int i = 0; i < g_size; i++) {
        if (g_songs[i].genre == genre) {
            genreCount++;
            wanted[hi] = g_songs[i];
            hi++;
        }
        else {
            nothing[ho] = g_songs[i];
            ho++;
        }
    }


    return wanted;
}

Song * getSongsFromDuration(int duration, int &durationsCount, int filter)
{
    Song * wanted = new Song[g_size];
    Song * nothing = new Song[g_size];
    durationsCount = 0;
    int hi = 0;
    int ho = 0;
    if (filter == 0) {
        for (int i = 0; i < g_size; i++) {
            if (g_songs[i].duration > duration) {
                durationsCount = durationsCount + 1;
                wanted[hi] = g_songs[i];
                hi++;
            }
        }
    }
    
    if (filter == 1) {
        for (int q = 0; q < g_size; q++) {
            if (g_songs[q].duration < duration) {
                durationsCount = durationsCount + 1;
                wanted[hi] = g_songs[q];
                hi++;
            }
        }
    }
    
    if (filter == 2) {
        for (int w = 0; w < g_size; w++) {
            if (g_songs[w].duration == duration) {
                durationsCount = durationsCount + 1;
                wanted[hi] = g_songs[w];
                hi++;
            }
        }
    }

    return wanted;
}

string * getUniqueArtists(int &uniqueCount)
{
    uniqueCount = 0;
    Song * wanted = new Song[g_size];

    for (int i = 0; i < g_size; i++) {
        int j = 0;
        for (j = 0; j < g_size; j++) {
            if (g_songs[i].artist == g_songs[j].artist) {
                break;
            }
        }
        if (i == j) {
                wanted[i] = g_songs[j];
                uniqueCount += 1;
            }
    }

    string dyna[g_size];
    for (int p = 0; p < g_size; p++) {
        dyna[p] = g_songs[p].name;
    }

    return dyna;
}

string getFavoriteArtist()
{
    string need;
    int prelim = 0;
    int count = 0;

    if (g_size == 0) {
        need = "NONE";
    }
    else {
        for (int i = 0; i < g_size; i++) {
            for (int j = 0; j < g_size; j++) {
                if (g_songs[i].artist == g_songs[j].artist) {
                    prelim += 1;
                }
            }

            if (count < prelim) {
                count = prelim;
                need = g_songs[i].artist;
            }
            prelim = 0;
        }
    }
    return need;
}