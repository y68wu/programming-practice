#include <stdlib.h>
#include <assert.h>
#include "queue.h"
#include "deque.h"

typedef void* (*Copy_data) (const void*);
typedef void (*Destroy_data) (void*);
typedef void (*Print_data) (const void*);

struct Queue {
    struct Deque* deque;
};

// queue_create(copy, destroy, print)
//  returns a pointer to heap allocated Queue
// Effects: allocates memory
// Time: O(1)

struct Queue* queue_create(Copy_data copy, Destroy_data destroy, Print_data print) {
    struct Queue* que = malloc(sizeof(struct Queue));
    que->deque = deque_create(copy, destroy, print);
    return que;
}

// queue_destroy(q) fress the heap allocated Queue
// Effects: frees memory
// Time: O(n);

void queue_destroy(struct Queue* q) {
    assert(q);

    deque_destroy(q->deque);
    free(q);
}

// queue_empty(q) returns true if q is empty
// Requires: q is not NULL
// Time: O(1)

bool queue_empty(const struct Queue* q) {
    assert(q);

    return deque_empty(q->deque);
}

// queue_enqueue(q, data) enqueues data onto q
// Effects: mutates *q
// Requires: q is not NULL
// Time: O(1)

void queue_enqueue(struct Queue* q, const void* data) {
    assert(q);
    assert(data);

    insert_back(q->deque, data);
}

// queue_dequeue(q) pops the front data from q
// Effects: mutates *q, de-allocates memory
// Requires: q is not NULL and not empty
// Time: O(1)

void queue_dequeue(struct Queue* q) {
    assert(q);

    remove_front(q->deque);
}

// queue_front(q) returns the front data from q
// Requires: q is not NULL and not empty
//           client must call destroy on returned pointer
// Time: O(1)

void* queue_front(const struct Queue* q) {
    assert(q);

    return deque_front(q->deque);
}

// queue_print(q) prints the queue from front to back
// Effects: produces output
// Requires: q is not NULL
// Time: O(n)

void queue_print(const struct Queue* q) {
    assert(q);

    deque_print_forward(q->deque);
}
