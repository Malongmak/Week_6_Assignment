#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_NAME_LEN 50

// Define the user structure
typedef struct User {
    int id;
    char name[MAX_NAME_LEN];
    struct User* friends[MAX_USERS]; 
    int friendCount;
} User;

// function to define the social network structure
typedef struct SocialNetwork {
    User* users[MAX_USERS];
    int userCount;
} SocialNetwork;

// function prototypes
SocialNetwork* createNetwork();
User* createUser(int id, const char* name);
void addUser(SocialNetwork* network, const char* name);
void addConnection(SocialNetwork* network, int id1, int id2);
void printAdjacencyList(SocialNetwork* network);
void dfs(User* user, int visited[], User* recommendations[], int* recCount);
void recommendConnections(SocialNetwork* network, int userId);
void printRecommendations(User* user, User* recommendations[], int recCount);

int main() {
    SocialNetwork* network = createNetwork();

    // function to add users
    addUser(network, "Samuel");
    addUser(network, "Magot");
    addUser(network, "Joshua");
    addUser(network, "David");
    addUser(network, "Ezekiel");

    // function to add connections
    addConnection(network, 0, 1); // Samuel <-> Magot
    addConnection(network, 0, 2); // Samuel <-> Joshua
    addConnection(network, 1, 2); // Magot <-> Joshua
    addConnection(network, 2, 3); // Joshua <-> David
    addConnection(network, 3, 4); // David <-> Ezekiel

    // function to print adjacency list
    printf("Adjacency List Representation:\n");
    printAdjacencyList(network);

    // function to recommend connections for each user
    for (int i = 0; i < network->userCount; i++) {
        printf("\nRecommendations for %s:\n", network->users[i]->name);
        recommendConnections(network, i);
    }

    return 0;
}

// function to create a new social network
SocialNetwork* createNetwork() {
    SocialNetwork* network = (SocialNetwork*)malloc(sizeof(SocialNetwork));
    network->userCount = 0;
    return network;
}

// function to create a new user
User* createUser(int id, const char* name) {
    User* user = (User*)malloc(sizeof(User));
    user->id = id;
    strncpy(user->name, name, MAX_NAME_LEN);
    user->friendCount = 0;
    return user;
}

// function to add a user to the network
void addUser(SocialNetwork* network, const char* name) {
    if (network->userCount < MAX_USERS) {
        User* user = createUser(network->userCount, name);
        network->users[network->userCount] = user;
        network->userCount++;
    } else {
        printf("Maximum user limit reached.\n");
    }
}

// function to add a connection between two users
void addConnection(SocialNetwork* network, int id1, int id2) {
    if (id1 < network->userCount && id2 < network->userCount && id1 != id2) {
        User* user1 = network->users[id1];
        User* user2 = network->users[id2];
        user1->friends[user1->friendCount++] = user2;
        user2->friends[user2->friendCount++] = user1; 
    }
}

// Print adjacency list representation of the graph
void printAdjacencyList(SocialNetwork* network) {
    for (int i = 0; i < network->userCount; i++) {
        User* user = network->users[i];
        printf("%s: ", user->name);
        for (int j = 0; j < user->friendCount; j++) {
            printf("%s ", user->friends[j]->name);
        }
        printf("\n");
    }
}

// Depth First Search to explore friends and find recommendations
void dfs(User* user, int visited[], User* recommendations[], int* recCount) {
    visited[user->id] = 1; 

    // function to check all friends of the current user
    for (int i = 0; i < user->friendCount; i++) {
        User* friend = user->friends[i];
        for (int j = 0; j < friend->friendCount; j++) {
            User* potential = friend->friends[j];
            if (!visited[potential->id] && potential != user) {
                // function to check if already recommended friend exists
                int alreadyFriend = 0;
                for (int k = 0; k < user->friendCount; k++) {
                    if (user->friends[k] == potential) {
                        alreadyFriend = 1; 
                        break;
                    }
                }
                if (!alreadyFriend) {
                    recommendations[(*recCount)++] = potential; 
                }
            }
        }
        if (!visited[friend->id]) {
            dfs(friend, visited, recommendations, recCount);
        }
    }
}

// function to recommend connections for specific users
void recommendConnections(SocialNetwork* network, int userId) {
    User* user = network->users[userId];
    int visited[MAX_USERS] = {0}; // Tracking visited users
    User* recommendations[MAX_USERS];
    int recCount = 0;

    // Perform DFS starting from this user
    dfs(user, visited, recommendations, &recCount);

    // Print recommendations
    printRecommendations(user, recommendations, recCount);
}

// function to print recommendations
void printRecommendations(User* user, User* recommendations[], int recCount) {
    if (recCount == 0) {
        printf("No recommendations available.\n");
    } else {
        for (int i = 0; i < recCount; i++) {
            printf("- %s\n", recommendations[i]->name);
        }
    }
}
