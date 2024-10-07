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

// function to define the Node structure
typedef struct Node {
    Product product;
    struct Node* left;
    struct Node* right;
} Node;

// function prototypes
Node* createNode(Product product);
Node* insert(Node* root, Product product);
Product* search(Node* root, const char* name);
int updateProduct(Node* root, const char* name, float price, int quantity);
void displaySorted(Node* root);
void trackOutOfStock(Node* root);

// function to create a new node
Node* createNode(Product product) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->product = product;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// function to insert products into tree
Node* insert(Node* root, Product product) {
    if (root == NULL) {
        return createNode(product);
    }
    if (strcmp(product.name, root->product.name) < 0) {
        root->left = insert(root->left, product);
    } else if (strcmp(product.name, root->product.name) > 0) {
        root->right = insert(root->right, product);
    }
    return root;
}

// function to search for a product
Product* search(Node* root, const char* name) {
    if (root == NULL) return NULL;
    if (strcmp(name, root->product.name) == 0) return &root->product;
    if (strcmp(name, root->product.name) < 0) return search(root->left, name);
    return search(root->right, name);
}

// function to update the price and quantity of a product
int updateProduct(Node* root, const char* name, float price, int quantity) {
    Product* product = search(root, name);
    if (product != NULL) {
        if (price >= 0) product->price = price;
        if (quantity >= 0) product->quantity = quantity;
        return 1; // Updated successfully
    }
    return 0; // return 0 if Product not found
}

// function to In-order traversal to display products in sorted order
void displaySorted(Node* root) {
    if (root != NULL) {
        displaySorted(root->left);
        printf("ID: %d, Name: %s, Price: %.2f, Quantity: %d\n", 
               root->product.product_id, root->product.name, 
               root->product.price, root->product.quantity);
        displaySorted(root->right);
    }
}

// function to track out-of-stock products
void trackOutOfStock(Node* root) {
    if (root != NULL) {
        trackOutOfStock(root->left);
        if (root->product.quantity == 0) {
            printf("Out of Stock - ID: %d, Name: %s\n", 
                   root->product.product_id, root->product.name);
        }
        trackOutOfStock(root->right);
    }
}

// function to run the program
int main() {
    Node* root = NULL;

    // product data
    Product p1 = {1, "Laptop", 999.99, 10};
    Product p2 = {2, "Mouse", 25.50, 0};
    Product p3 = {3, "Keyboard", 45.00, 5};
    Product p4 = {4, "Monitor", 199.99, 0};
    Product p5 = {5, "Headphones", 49.99, 0};
    Product p6 = {6, "Mousepad", 9.99, 0};


    // function to insert products into tree
    root = insert(root, p1);
    root = insert(root, p2);
    root = insert(root, p3);
    root = insert(root, p4);

    // Searching for a product
    char searchName[] = "Mouse";
    Product* foundProduct = search(root, searchName);
    if (foundProduct) {
        printf("Found Product: ID: %d, Name: %s, Price: %.2f, Quantity: %d\n", 
               foundProduct->product_id, foundProduct->name, 
               foundProduct->price, foundProduct->quantity);
    } else {
        printf("Product '%s' not found.\n", searchName);
    }

    //  function to update product details
    if (updateProduct(root, "Keyboard", 40.00, 3)) {
        printf("Product 'Keyboard' updated successfully.\n");
    } else {
        printf("Product 'Keyboard' not found for update.\n");
    }

    // function to display all products in sorted order
    printf("\nSorted Products:\n");
    displaySorted(root);

    // function to track out-of-stock products
    printf("\nOut of Stock Products:\n");
    trackOutOfStock(root);


    return 0;
}