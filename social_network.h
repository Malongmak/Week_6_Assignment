#ifndef SOCIAL_NETWORK_H
#define SOCIAL_NETWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_NAME_LEN 50

// User structure
typedef struct User {
    int id;
    char name[MAX_NAME_LEN];
    struct User* friends[MAX_USERS];
    int friendCount;
} User;

// Social network structure
typedef struct SocialNetwork {
    User* users[MAX_USERS];
    int userCount;
} SocialNetwork;

// Function prototypes
SocialNetwork* createNetwork();
User* createUser(int id, const char* name);
void addUser(SocialNetwork* network, const char* name);
void addConnection(SocialNetwork* network, int id1, int id2);
void printAdjacencyList(SocialNetwork* network);
void recommendConnections(SocialNetwork* network, int userId);

#endif // SOCIAL_NETWORK_H
