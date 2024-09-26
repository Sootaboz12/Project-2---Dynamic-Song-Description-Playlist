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
