#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "deque.h"
// your include goes here


// ================= DO NOT CHANGE THESE LINES =================
typedef void* (*Copy_data)    (const void*);
typedef void  (*Destroy_data) (void*);
typedef void  (*Print_data)   (const void*);
// =============================================================


struct Node {
    void* data;         // actual data stored
    struct Node* next;  // pointer to next node
    struct Node* prev;  // pointer to previous node
};

static struct Node* node_create(const void* data, Copy_data copy_func) {
    assert(data);

    struct Node* node = malloc(sizeof(struct Node));
    node->data = copy_func(data);
    node->next = NULL;
    node->prev = NULL;
    return node;
}

static void node_destroy(struct Node* node, Destroy_data destory_func) {
    assert(node);

    struct Node* temp = node;
    while (temp != NULL) {
        destory_func(temp->data);
        struct Node* next = temp->next;
        free(temp);
        temp = next;
    }
}

struct Deque {
    struct Node* head;
    struct Node* tail;
    Copy_data copy_func;
    Destroy_data destroy_func;
    Print_data print_func;
};

// deque_create(copy, destroy, print) returns a pointer to heap allocated Deque
// Effects: allocates memory, caller must free
// Time: O(1)

struct Deque* deque_create(Copy_data copy, Destroy_data destroy, Print_data print) {
    struct Deque* deq = malloc(sizeof(struct Deque));
    deq->copy_func = copy;
    deq->destroy_func = destroy;
    deq->print_func = print;
    deq->head = NULL;
    deq->tail = NULL;
    return deq;
}

// destroy_deque(deq) fress the heap allocated Deque
// Effects: frees memory
// Time: O(n)

void deque_destroy(struct Deque* deq) {
    assert(deq);
    node_destroy(deq->head, deq->destroy_func);
    node_destroy(deq->tail, deq->destroy_func);
    free(deq);
}

// deque_empty(deq) returns true if deq is empty, and false otherwise
// Requires: deq is not NULL
// Time: O(1)

bool deque_empty(const struct Deque* deq) {
    assert(deq);
    return (deq->head == NULL) && (deq->tail == NULL);
}

// insert_front(deq, data) inserts data in front of deq
// Effects: mutates *deq
// Requires: deq is not NULL
// Time: O(1)

void insert_front(struct Deque* deq, const void* data) {
    assert(deq);
    assert(data);

    struct Node* node = node_create(data, deq->copy_func);
    node->next = deq->head;
    deq->head->prev = node;
    deq->head = node;
}

// insert_back(deq, data) inserts data at back of deq
// Effects: mutates *deq
// Requires: deq is not NULL
// Time: O(1)

void insert_back(struct Deque* deq, const void* data) {
    assert(deq);
    assert(data);

    struct Node* node = node_create(data, deq->copy_func);
    node->prev = deq->tail;
    deq->tail->next = node;
    deq->tail = node;
}

// remove_front(deq) removes the front data from deq
// Effects: mutates *deq, de-allocates memory
// Requires: deq is not NULL and not empty
// Time: O(1)

void remove_front(struct Deque* deq) {
    assert(deq);

    struct Node* pre_front_node = deq->head;
    struct Node* cur_front_node = deq->head->next;
    cur_front_node->prev = NULL;
    pre_front_node->next = NULL;
    node_destroy(pre_front_node, deq->destroy_func);
    deq->head = cur_front_node;
}


// remove_back(deq) removes the back data from deq
// Effects: mutates *deq, de-allocates memory
// Requires: deq is not NULL and not empty
// Time: O(1)

void remove_back(struct Deque* deq) {
    assert(deq);

    struct Node* pre_back_node = deq->tail;
    struct Node* cur_back_node = deq->tail->prev;
    pre_back_node->prev = NULL;
    cur_back_node->next = NULL;
    node_destroy(pre_back_node, deq->destroy_func);
    deq->tail = cur_back_node;
}

// deque_front(deq) returns the front data of deq
// Effects: allocates memory
// Requires: deq is not NULL and not empty
//           client must call destroy on the returned pointer
// Time: O(1)

void* deque_front(const struct Deque* deq) {
    assert(deq);

    return deq->head->data;
}

// deque_back(deq) returns the back data of deq
// Effects: allocates memory
// Requires: deq is not NULL and not empty
//           client must call destroy on the returned pointer
// Time: O(1)

void* deque_back(const struct Deque* deq) {
    assert(deq);

    return deq->tail->data;
}

// deque_print_forward(deq) prints the data in order
// Requires: deq is not NULL
// Time: O(n)

void deque_print_forward(const struct Deque* deq) {
    assert(deq);

    struct Node* front_node = deq->head;

    while(front_node != NULL) {
        deq->print_func(front_node->data);
        front_node = front_node->next;
    }
}

// deque_print_backward(deq) prints the data in reverse order
// Requires: deq is not NULL
// Time: O(n)

void deque_print_backward(const struct Deque* deq) {
    assert(deq);

    struct Node* back_node = deq->tail;

    while(back_node->prev != NULL) {
        deq->print_func(back_node->data);
        back_node = back_node->prev;
    }
}
