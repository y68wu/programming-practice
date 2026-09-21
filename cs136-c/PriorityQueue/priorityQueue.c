#include <stdlib.h>
#include "priorityQueue.h"
// add your include here

// ======================DO NOT MODIFY STRUCTURE DEFINTIONS ============================
typedef struct Patient {
    int priority;
    int time_stamp;         // think the purpose of this field
    char* name;
} Patient;

typedef struct PriorityQueue {
    int len;
    int cap;
    int curr_time_stamp;    // think the purpose of this field
    struct Patient** patients;
} PQ;
// =====================================================================================

// pq_create() creates a heap allocated priority queue
// Effects: allocates memory, caller must free
// Time: O(1)

PQ* pq_create() {
    // your implementation goes here
    return NULL;
}

// pq_destroy(pq) frees the heap allocated pq
// Effects: deallocates memory
// Time: O(n)

void pq_destroy(PQ* pq) {
    // your implementation goes here
}

// pq_size(pq) returns the number of names stored in pq
// Requires: heap is not NULL
// Time: O(1)

int pq_size(const PQ* pq) {
    // your implementation goes here
    return 0;
}

// pq_insert(pq, priority, name) inserts name and its priority into pq
//  priroity with 5 has a higher priority with 3
//  if priority already exists, then it follows "First in First Out" rule
// Effects: mutates *pq
// Requires: pq is not NULL, name is not NULL, priority >= 1
// Time: amoritized(log n + m)

void pq_insert(PQ* pq, int priority, const char* name) {
    // your implementation goes here
}

// pq_remove(pq) removes and returns the name with the highest priority
//  writes the removed priority into *priority
// Effects: mutates *pq, mutates *priority
// Requires: pq is not NULL and not empty, priority is not NULL
//           caller must free returned pointer
// Time: O(log n)

char* pq_remove(PQ* pq, int* priority) {
    // your implementation goes here
    return NULL;
}

// heap_sort(names, priorities, len) uses heap to sort the two arrays
//  both arrays have same length, and each name in names is associated with the
//  priority at the same index in priorities
// Effects: mutates* names and *priorities
// Requires:names != NULL and priorities != NULL and len > 0
// Time: O(n log n)

void heap_sort(char** names, int* priorities, int len) {
    // your implementation goes here
}
