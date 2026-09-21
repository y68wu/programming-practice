#include <stdlib.h>
#include <assert.h>
#include "stack.h"
#include "deque.h"
// your include goes here

typedef void* (*Copy_data) (const void*);
typedef void (*Destroy_data) (void*);
typedef void (*Print_data) (const void*);

struct Stack {
    struct Deque* deque;
};

// stack_create(copy, desotry, print) 
//  returns a pointer to heap allocated Stack
// Effects: allocates memory, caller must free
// Time: O(1)

struct Stack* stack_create(Copy_data copy, Destroy_data destroy, Print_data print) {
    struct Stack* stack = malloc(sizeof(struct Stack));
    stack->deque = deque_create(copy, destroy, print);
    return stack;
}

// stack_destroy(stk) fress the heap allocated Stack
// Effects: frees memory
// Time: O(n)

void stack_destroy(struct Stack* stk) {
    assert(stk);

    deque_destroy(stk->deque);
    free(stk);
}

// stack_empty(stk) returns true if stk is empty
// Requires: stk is not NULL
// Time: O(1)

bool stack_empty(const struct Stack* stk) {
    assert(stk);

    return deque_empty(stk->deque);
}

// stack_push(stk, data) pushes data onto stk
// Effects: mutates *stk
// Requires: stk is not NULL
// Time: O(1)

void stack_push(struct Stack* stk, const void* data) {
    assert(stk);
    assert(data);

    insert_back(stk->deque, data);
}

// stack_pop(stk) pops and returns the top data from stk
// Effects: mutates *stk, de-allocates memory
// Requires: stk is not NULL and not empty
// Time: O(1)

void stack_pop(struct Stack* stk) {
    assert(stk);
    remove_back(stk->deque);
}

// stack_top(stk) returns the top data from stk
// Requires: stk is not NULL and not empty
//           client must call destroy on returned pointer
// Time: O(1)

void* stack_top(const struct Stack* stk) {
    assert(stk);
    return deque_back(stk->deque);
}

void stack_print(const struct Stack* stk) {
    assert(stk);
    deque_print_backward(stk->deque);
}
