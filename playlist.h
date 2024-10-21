#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // For sleep function

// Define the song structure
typedef struct Song {
    char name[100];
    int duration; // Duration in seconds
    struct Song* next;
} Song;

// Function prototypes
Song* createSong(const char* name, int duration);
void appendSong(Song** head, const char* name, int duration);
void playPlaylist(Song* head);
void freePlaylist(Song* head);

#endif // PLAYLIST_H
