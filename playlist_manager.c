#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char data[40];
    struct node* next;
    struct node* prev;
};

char temp[40];
struct node* head = NULL;
struct node* current_node = NULL;

void insert() {
    printf("Enter Music Name:\n");
    while ((getchar()) != '\n');
    scanf("%[^\n]%*c", temp);

    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    strcpy(new_node->data, temp);
    if (head == NULL) {
        new_node->next = new_node->prev = new_node;
        head = current_node = new_node;
        return;
    }
    struct node* last = head->prev;
    new_node->prev = last;
    last->next = new_node;
    new_node->next = head;
    head->prev = new_node;
}

void Delete_element() {
    if (head == NULL) {
        printf("No Music is there to delete!\n");
        return;
    }
    printf("Enter Music Name to delete:\n");
    while ((getchar()) != '\n');
    scanf("%[^\n]%*c", temp);
    printf("\n");
    struct node* ptr = head;
    do {
        if (ptr->next == ptr && strcmp(ptr->data, temp) == 0) {
            printf("One file deleted! Playlist is Empty Now!\n");
            head = NULL;
            free(ptr);
            return;
        } else if (strcmp(ptr->data, temp) == 0) {
            struct node* prev = ptr->prev;
            struct node* next = ptr->next;
            prev->next = next;
            next->prev = prev;
            if (ptr == head) {
                head = next; // Update head if needed
            }
            free(ptr);
            printf("Music deleted!\n");
            return;
        }
        ptr = ptr->next;
    } while (ptr != head);
    printf("No Music file is there!\n");
}

void show() {
    if (head == NULL) {
        printf("Playlist is Empty!\n");
        return;
    }
    struct node* show_ptr = head;
    printf("\nDisplaying Playlist:\n");
    int i = 1;
    do {
        printf("Song %d: %s\n", i, show_ptr->data);
        i++;
        show_ptr = show_ptr->next;
    } while (show_ptr != head);
}

void next_node() {
    if (current_node == NULL) {
        printf("No songs in Playlist!\n");
    } else {
        current_node = current_node->next;
        printf("Playing Next Song: %s\n", current_node->data);
    }
}

void prev_node() {
    if (current_node == NULL) {
        printf("No songs in Playlist!\n");
    } else {
        current_node = current_node->prev;
        printf("Playing Previous Song: %s\n", current_node->data);
    }
}

void first_node() {
    if (head == NULL) {
        printf("Playlist is Empty!\n");
    } else {
        printf("Playing First Music: %s\n", head->data);
    }
}

void last_node() {
    if (head == NULL) {
        printf("Playlist is Empty!\n");
    } else {
        printf("Playing Last Music: %s\n", head->prev->data);
    }
}

void freePlaylist() {
    if (head == NULL) return;
    struct node* current = head;
    struct node* next;
    do {
        next = current->next;
        free(current);
        current = next;
    } while (current != head);
    head = NULL; // Reset head to NULL
}

int main() {
    int choice;
    while (1) {
        printf("\n-----Song Playlist Application-----\n");
        printf("1. Add Music\n");
        printf("2. Remove Music\n");
        printf("3. Show Playlist\n");
        printf("4. Play next file\n");
        printf("5. Play previous file\n");
        printf("6. Play first file\n");
        printf("7. Play last file\n");
        printf("8. Exit\n\n");
        scanf("%d", &choice);

        if (choice == 1)
            insert();
        else if (choice == 2)
            Delete_element();
        else if (choice == 3)
            show();
        else if (choice == 4)
            next_node();
        else if (choice == 5)
            prev_node();
        else if (choice == 6)
            first_node();
        else if (choice == 7)
            last_node();
        else if (choice == 8) {
            freePlaylist(); // Free memory before exiting
            break; // Exit the loop
        } else {
            printf("Invalid choice, please try again.\n");
        }
    }
    return 0;
}
