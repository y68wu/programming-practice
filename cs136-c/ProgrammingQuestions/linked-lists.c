#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
// add your include here


// ================= DO NOT CHANGE THESE CODE ==================
struct Node {
    int val;
    struct Node* next;
};

// node_create(n):
//  creates a node in heap memory with val equals to n
// Effects: allocates memory
// Time: O(1)
static struct Node* node_create(int n) {
    struct Node* node = malloc(sizeof(struct Node));
    node->val = n;
    node->next = NULL;
    return node;
}

// node_destroy(node)
//  frees the linked list in heap memory
// Effects: de-allocates node
// Time: O(n)
static void node_destroy(struct Node* node) {
    while (node != NULL) {
        struct Node* temp = node->next;
        free(node);
        node = temp;
    }
}

// create_list(n)
//  converts arr into linked list by preserving the order of elements
// Effects: allocates memory, client must call node_destroy
// Time: O(n)
static struct Node* create_list(const int* arr, int len) {
    assert(len >= 1);

    struct Node* head = node_create(arr[0]);
    struct Node* tail = head;
    for (int i = 1; i < len; i++) {
        struct Node* node = node_create(arr[i]);
        tail->next = node;
        tail = node;
    }
    return head;
}

// print_list(node) prints the linked list
// Effects: produces output
// Time: O(n)
static void print_list(const struct Node* node) {
    if (node == NULL) return;
    printf("%d", node->val);
    const struct Node* curr = node->next;
    while (curr) {
        printf(" -> %d", curr->val);
        curr = curr->next;
    }
    printf("\n");
}
// =============================================================

// reverse_list(root) reverses the linked list
// Effects: mutates *root
// Time: O(n)
void reverse_list(struct Node** root) {
    struct Node* prev = *root;
    struct Node* curr = *root;

    while (curr != NULL) {
        struct Node* temp = curr->next;
        curr->next = prev; 
        prev = curr;
        curr = temp;
    }

    *root = prev;
}

// remove_duplicate(root) removes all nodes that contains duplicate val
// Effects: de-allocates memory
// Time: O(n)
void remove_duplicate(struct Node* root) {
    struct Node* prev = root;
    struct Node* curr = root->next;

    while (curr) {
        struct Node* temp = curr->next;
        if (prev->val == curr->val) {
            free(curr);
            prev->next = temp;
            curr = temp;
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
}

// get_last(root) returns pointer to the last node in linked-list
// Time: O(n)
struct Node* get_last(struct Node* root) {
    struct Node* prev = root;
    while (prev->next != root) {
        prev = prev->next;
    }
    return prev;
}

// merge_two_sorted_lists(r1, r2)
//  combines two sorted linked-lists into one, and
//  returns the pointer to the head node of the combined linked-list
// Time: O(m + n)
struct Node* merge_two_sorted_lists(struct Node* r1, struct Node* r2) {
    struct Node* front = NULL;
    struct Node* back = NULL;
    struct Node* n1 = r1;
    struct Node* n2 = r2;

    while (n1 && n2) {
        if (n1->val <= n2->val) {
            if (front == NULL) {
                front = n1;
                back = n1;
            } else {
                back->next = n1;
                back = n1;
            }
            n1 = n1->next;
        } else {
            if(front == NULL) {
                front = n2;
                back = n2;
            } else {
                back->next = n2;
                back = n2;
            }
            n2 = n2->next
        }
    }

    while (n1) {
        back->next = n1;
    }

    while (n2) {
        back->next = n2;
    }

    return front;
}


// find_intersection(r1, r2) returns the pointer to the head node
//  of the intersection of two linked-list.
// Time: O(mn)
struct Node* find_intersection(struct Node* r1, struct Node* r2) {
    struct Node* n1 = r1;
    struct Node* n2 = r2;

    whlie(n1 != n2) {
        if (n1 == NULL) {
            n1 = r1;
        } else {
            n1 = n1->next;
        }

        if (n2 == NULL) {
            n2 = r2;
        } else {
            n2 = n2->next;
        }
    }

    return n2;
}

int main() {
    srand(time(NULL));
    printf("%d\n", rand() % 100);
}
