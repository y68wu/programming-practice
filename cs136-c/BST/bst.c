#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "bst.h"


// ================= DO NOT CHANGE THESE LINES =================
static struct Node* node_create(const int num) {
    struct Node* node = malloc(sizeof(struct Node));
    node->key = num;
    node->left = NULL;
    node->right = NULL;
    return node;
}

static void node_destroy(struct Node* node) {
    if (node) {
        node_destroy(node->left);
        node_destroy(node->right);
        free(node);
    }
}

struct BST* bst_create() {
    struct BST* bst = malloc(sizeof(struct BST));
    bst->root = NULL;
    return bst;
}

void bst_insert(struct BST* bst, const int num) {
    assert(bst);

    struct Node* node = node_create(num);       // creates a new node
    // check if tree is empty
    if (bst->root == NULL) {
        bst->root = node;
        return;
    }

    struct Node* curr = bst->root;
    while (curr != NULL) {
        if (curr->key == num) {         // key exists
            node_destroy(node);
            break;
        } else if (curr->key < num) {   // go right
            if (curr->right != NULL) {
                curr = curr->right;
            } else {
                curr->right = node;
                break;
            }
        } else {                        // go left
            if (curr->left != NULL) {
                curr = curr->left;
            } else {
                curr->left = node;
                break;
            }
        }
    }
}

static struct Node* node_remove_key(struct Node* node, const int num) {
    if (node == NULL) return node;

    if (node->key < num) {          // go right
        node->right = node_remove_key(node->right, num);
    } else if (node->key > num) {   // go left
        node->left = node_remove_key(node->left, num);
    } else {                        // found the key
        if (node->left == NULL && node->right == NULL) {        // removing leaf node
            free(node);
            return NULL;
        }
        if (node->right == NULL) {                              // node does not have right child
            struct Node* temp = node->left;
            free(node);
            return temp;
        }
        if (node->left == NULL) {                               // node does not have left child
            struct Node* temp = node->right;
            free(node);
            return temp;
        }
        // neither child is not NULL, find left-most child in the right subtree
        struct Node* prev = NULL;
        struct Node* curr = node->right;
        while (curr->left != NULL) {
            prev = curr;
            curr = curr->left;
        }
        node->key = curr->key;
        if (prev == NULL) {
            node->right = curr->right;
        } else {
            prev->left = curr->right;
        }
        free(curr);
    }
    return node;
}

void bst_remove(struct BST* bst, const int num) {
    assert(bst);

    bst->root = node_remove_key(bst->root, num);
}
// =============================================================

void count_leaf_helper(const struct Node* node, int* leaf) {
    if (node == NULL) {
        return;
    }

    if (node->left == NULL && node->right == NULL) {
        *leaf += 1;
    }

    count_leaf_helper(node->left, leaf);
    count_leaf_helper(node->right, leaf);
}

// count_leaf(bst, leaf) stores the number of leaf nodes of bst in leaf
// Effects: mutates *leaf
// Requires: bst is not NULL, leaf is not NULL
// Time: O(n)
void count_leaf(const struct BST* bst, int* leaf) {
    *leaf = 0;
    count_leaf_helper(bst->root, leaf);
}

void count_total_helper(const struct Node* node, int *total) {
    if (node == NULL) {
        return;
    }

    *total += 1;
    count_total_helper(node->left, total);
    count_total_helper(node->right, total);
}

// count_all(bst, leaf, total)
//  stores the number of leaf nodes of bst in leaf
//  stores the total number of nodes of bst in total
// Effects: mutates *leaf and *total
// Requires: bst is not NULL, leaf is not NULL, total is not NULL
// Time: O(n)
void count_all(const struct BST* bst, int* leaf, int* total) {
    *total = 0;
    count_leaf(bst, leaf);
    *total = 0;
    count_total_helper(bst, total);
}

static int bst_stats_helper(const struct Node* node) {
    if (node == NULL) {
        return 0;
    }

    int left_deep = bst_stats_helper(node->left);
    int right_deep = bst_stats_helper(node->right);

    if (left_deep > right_deep) {
        return 1 + left_deep;
    } else {
        return 1 + right_deep;
    }
}

// bst_stats(bst, leaf, total) returns the height of bst
//  stores the number of leaf nodes of bst in leaf
//  stores the total number of nodes of bst in total
// Effects: mutates *leaf and *total
// Requires: bst is not NULL, leaf is not NULL, total is not NULL
// Time: O(n)
int bst_stats(const struct BST* bst, int* leaf, int* total) {
    count_all(bst, leaf, total);
    return bst_stats_helper(bst->root);
}

static void deepest_node_helper(const struct Node* node, int height, int* deepest, struct Node** deep_node) {
    if (node != NULL) {
        if (height >= *deepest) {
            *deepest = height;
            *deep_node = node;
        }

        int new_height = height + 1;
        deepest_node_helper(node->left, new_height, deepest, deep_node);
        deepest_node_helper(node->right, new_height, deepest, deep_node);
    }
}

// bst_deepest_node(bst) returns the pointer to the deepest node in bst
//  returns NULL is bst is empty
//  if mulitple nodes are with the same depth, returns the rightmost one
// Requires: bst is not NULL
// Time: O(n)
struct Node* deepest_node(const struct BST* bst) {
    struct Node* deep_node = NULL;
    int deepest = 0;
    deepest_node_helper(bst->root, 0, &deepest, &deep_node);
    return deep_node;
}

static void to_sorted_array_helper(const struct Node* node, int* arr, int* len) {
    if (node == NULL) {
        return;
    }

    to_sorted_array_helper(node->left, arr, len);
    arr[len] = node->key;
    len += 1;
    to_sorted_array_helper(node->left, arr, len);
}

// bst_to_sorted_array(bst, len) 
//  returns a dynamic array containing all keys in bst in ascending order
//  stores the length of array in len
// Effects: allocates memory, caller must free
//          mutates len
// Requires: bst is not NULL and bst is not empty
// Time: O(n)
int* bst_to_sorted_array(const struct BST* bst, int* len) {
    // your implementation goes here

    const int max_len = 1000;
    int* arr = malloc(sizeof(int) * max_len);
    int len = 0;
    to_sorted_array_helper(bst->root, arr, &len);
    return arr;
}

static struct Node* to_bst_helper(int* arr, int start, int end) {
    if (start > end) {
        return NULL;
    }

    int mid = (start + end) / 2;
    struct Node* node = node_create(arr[mid]);
    node->left = to_bst_helper(arr, start, mid - 1);
    node->right = to_bst_helper(arr, mid + 1, end);
    return node;
}

// sorted_array_to_balanced_bst(arr, len)
//  returns a balanced BST containing all elements in arr
// Effects: allocates memory, caller must free
// Requires: len > 0
// Time: O(n)
struct BST* sorted_array_to_balanced_bst(int* arr, const int len) {
    int start = 0;
    int end = len - 1;
    struct BST* bst = bst_create();
    bst->root = to_bst_helper(arr, start, end);
    return bst;
}

static void* destory_helper(struct Node* node) {
    if(node == NULL) {
        return;
    }

    destory_helper(node->left);
    destory_helper(node->right);
    free(node);
}

// bst_destroy_recursive(bst) frees the heap allocated bst
// Effects: frees memory
// Requires: use recursion only
// Time: O(n)
void bst_destroy_recursive(struct BST* bst) {
    destory_helper(bst->root);
    free(bst);
}

// bst_destroy_iterative(bst) frees the heap allocated bst
// Effects: frees memory
// Requires: use iteration only
// Time: O(n)
void bst_destroy_iterative(struct BST* bst) {
    // your implementation goes here
}

