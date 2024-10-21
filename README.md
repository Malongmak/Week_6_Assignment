Week 6 Assignment: Data Structures and Algorithms (DSA)
This assignment focuses on implementing data structures and algorithms that are commonly used in social networking applications and playlist management systems. The goal is to reinforce concepts of data organization, memory management, and algorithm efficiency.

Overview
Social Network
File: social_network.h and main.c
Purpose: Implement a basic social networking application.
Key Features:
Create a social network with users.
Add connections (friendships) between users.
Print an adjacency list representing user connections.
Recommend potential friends based on existing connections using Depth First Search (DFS).
Playlist Management
File: playlist.h and main.c
Purpose: Manage a simple music playlist.
Key Features:
Create and append songs with specified durations.
Play songs sequentially, displaying each song's name and duration.
Automatically free memory once playback is complete.
Learning Objectives
Understand and implement linked lists for dynamic data management.
Apply algorithms for traversing and searching through data structures (e.g., DFS for recommendations).
Enhance skills in memory management in C, including allocation and deallocation of resources.
Compilation and Execution
For Social Network
Compile:

bash
Copy code
gcc main.c -o social_network
Run:

bash
Copy code
./social_network
For Playlist Management
Compile:

bash
Copy code
gcc main.c -o playlist
Run:

bash
Copy code
./playlist
Expected Outputs
Social Network:

Displays the adjacency list of user connections.
Outputs friend recommendations for each user.
Playlist Management:

Outputs the currently playing song and its duration sequentially.
Concludes with a message when the playlist finishes.
Conclusion
This assignment serves as a practical application of data structures and algorithms in real-world scenarios, enhancing understanding of how they can be effectively used to solve complex problems.