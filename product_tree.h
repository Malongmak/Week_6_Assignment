#ifndef PRODUCT_TREE_H
#define PRODUCT_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the Product structure
typedef struct Product {
    int product_id;
    char name[50];
    float price;
    int quantity;
} Product;

// Define the Node structure
typedef struct Node {
    Product product;
    struct Node* left;
    struct Node* right;
} Node;

// Function prototypes
Node* createNode(Product product);
Node* insert(Node* root, Product product);
Product* search(Node* root, const char* name);
int updateProduct(Node* root, const char* name, float price, int quantity);
void displaySorted(Node* root);
void trackOutOfStock(Node* root);

#endif // PRODUCT_TREE_H
