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

// Function to create a new song
Song* createSong(const char* name, int duration) {
    Song* newSong = (Song*)malloc(sizeof(Song));
    if (!newSong) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    strncpy(newSong->name, name, sizeof(newSong->name) - 1);
    newSong->name[sizeof(newSong->name) - 1] = '\0'; 
    newSong->duration = duration;
    newSong->next = NULL;
    return newSong;
}

// function to append a song to the playlist
void appendSong(Song** head, const char* name, int duration) {
    Song* newSong = createSong(name, duration);
    if (*head == NULL) {
        *head = newSong;
    } else {
        Song* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newSong;
    }
}

// Function to play the playlist
void playPlaylist(Song* head) {
    Song* current = head;
    while (current != NULL) {
        printf("Now playing: %s (Duration: %d seconds)\n", current->name, current->duration);
        sleep(current->duration); // Sleep for the duration of the song
        current = current->next;
    }
    printf("Playlist finished!\n");
}

// Function to free the memory of the playlist
void freePlaylist(Song* head) {
    Song* current = head;
    while (current != NULL) {
        Song* temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    Song* playlist = NULL;

    // Add some songs to the playlist
    appendSong(&playlist, "Mama mira", 3);
    appendSong(&playlist, "Nmempata yesu", 15);
    appendSong(&playlist, "Otumwa", 18);
    appendSong(&playlist, "We Must Be Together", 16);
    appendSong(&playlist, "Display", 12);
    appendSong(&playlist, "Marry", 14);
    appendSong(&playlist, "Kwa kwa", 17);

    // function to play the playlist
    playPlaylist(playlist);

    // function to free the memory
    freePlaylist(playlist);

    return 0;
}