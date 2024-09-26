
/*
Author: Mohammad Islam
Course: CSCI 137
Instructor: Genady Maryash
Assingment: Project 2 Task A

Project 2 Task A: Music playlist
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int g_curr_size = 2;
int g_number_of_songs = 0;

string *g_song_names = new string[g_curr_size];
string *g_artist_names = new string[g_curr_size];
int *g_song_durations = new int[g_curr_size];
string *g_genres = new string[g_curr_size];

void allocateNew()
{
    string* f_song_names = new string[g_curr_size * 2];
    int* f_song_durations = new int[g_curr_size * 2];
    string* f_artist_names = new string[g_curr_size * 2];
    string* f_genres = new string[g_curr_size * 2];

    for (int i = 0; i < g_curr_size; i++) {
        f_song_names[i] = g_song_names[i];
        f_artist_names[i] = g_artist_names[i];
        f_song_durations[i] = g_song_durations[i];
        f_genres[i] = g_genres[i];
    }

    delete [] g_song_names;
    delete [] g_artist_names;
    delete [] g_song_durations;
    delete [] g_genres;

    g_song_names = f_song_names;
    g_artist_names = f_artist_names;
    g_song_durations = f_song_durations;
    g_genres = f_genres;

    g_curr_size = g_curr_size * 2;
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

    g_song_names[0] = song_name;
    g_artist_names[0] = artist_name;
    g_genres[0] = genre;
    g_song_durations[0] = duration;

    g_number_of_songs = g_number_of_songs + 1;

    while (getline(fin, line)) {

        if (g_number_of_songs == g_curr_size) {
            allocateNew();
        }

        getline(fin, song_name, ':');
        getline(fin, artist_name, '-');
        getline(fin, genre, '-');
        getline(fin, duration_prelims, ' ');

        duration = stoi(duration_prelims);

        g_song_names[g_number_of_songs] = song_name;
        g_artist_names[g_number_of_songs] = artist_name;
        g_song_durations[g_number_of_songs] = duration;
        g_genres[g_number_of_songs] = genre;

        g_number_of_songs++;
    }
    
    g_number_of_songs = g_number_of_songs - 1;
}

string * getGenreSongs(string genre, int &genreCount)
{
    string * wanted = new string[g_number_of_songs];
    string * nothing = new string[g_number_of_songs];
    int * ptr = &genreCount;
    int count = 0;
    int hi = 0;
    int ho = 0;
    for (int i = 0; i < g_number_of_songs; i++) {
        if (g_genres[i] == genre) {
            count++;
            wanted[hi] = g_song_names[i];
            hi++;
        }
        else {
            nothing[ho] = g_song_names[i];
            ho++;
        }
    }
    *ptr = count;

    return wanted;
}

string * getSongsFromDuration(int duration, int &durationsCount, int filter)
{
    string * wanted = new string[g_number_of_songs];
    string * nothing = new string[g_number_of_songs];
    durationsCount = 0;
    int hi = 0;
    int ho = 0;

    if (filter == 0) {
        for (int i = 0; i < g_number_of_songs; i++) {
            if (g_song_durations[i] > duration) {
                durationsCount = durationsCount + 1;
                wanted[hi] = g_song_names[i];
                hi++;
            }
            else {
                nothing[ho] = g_song_names[i];
                ho++;
            }
        }
    }
    
    if (filter == 1) {
        for (int q = 0; q < g_number_of_songs; q++) {
            if (g_song_durations[q] < duration) {
                durationsCount = durationsCount + 1;
                wanted[hi] = g_song_names[q];
                hi++;
            }
            else {
                nothing[ho] = g_song_names[q];
                ho++;
            }
        }
    }
    
    if (filter == 2) {
        for (int w = 0; w < g_number_of_songs; w++) {
            if (g_song_durations[w] == duration) {
                durationsCount = durationsCount + 1;
                wanted[hi] = g_song_names[w];
                hi++;
            }
            else {
                nothing[ho] = g_song_names[w];
                ho++;
            }
        }
    }

    return wanted;
}

string * getUniqueArtists(int &uniqueCount)
{
    uniqueCount = 0;
    string * wanted = new string[g_number_of_songs];

    for (int i = 0; i < g_number_of_songs; i++) {
        int j = 0;
        for (j = 0; j < g_number_of_songs; j++) {
            if (g_artist_names[i] == g_artist_names[j]) {
                break;
            }
        }
        if (i == j) {
                wanted[i] = g_artist_names[j];
                uniqueCount += 1;
            }
    }

    return wanted;
}
 
string getFavoriteArtist() 
{
    string need;
    int prelim = 0;
    int count = 0;

    if (g_number_of_songs == 0) {
        need = "NONE";
    }
    else {
        for (int i = 0; i < g_number_of_songs; i++) {
            for (int j = 0; j < g_number_of_songs; j++) {
                if (g_artist_names[i] == g_artist_names[j]) {
                    prelim += 1;
                }
            }

            if (count < prelim) {
                count = prelim;
                need = g_artist_names[i];
            }
            prelim = 0;
        }
    }
    return need;
}
