#include <stdlib.h>
#include "sequence.h"
#include <assert.h>
// add your include here

// ================= DO NOT CHANGE THESE LINES =================
typedef void* (*Copy_data)    (const void*);
typedef void  (*Destroy_data) (void*);
typedef void  (*Print_data)   (const void*);
// =============================================================


struct Sequence {
    Copy_data copy;
    Print_data print;
    Destroy_data destroy;

    int row;
    int column;
    void*** data;
};

// seq_create(row, col, print, destroy)
//  returns a pointer to heap allocated Sequence
// Effects: allocates memory, caller must free
// Time: O(row * col)

struct Sequence* seq_create(const int row, const int col, 
                            Copy_data copy, Print_data print, Destroy_data destroy) {
    
    struct Sequence* seq = malloc(sizeof(struct Sequence));
    seq->copy = copy;
    seq->print = print;
    seq->destroy = destroy;
    seq->row = row;
    seq->column = col;

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            seq->data[i][j] = NULL;
        }
    }

    return seq;
}

// seq_destroy(seq) fress the heap allocated seq
// Effects: frees memory
// Time: O(r * c * k) where O(k) is destroy

void seq_destroy(struct Sequence* seq) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            seq->destroy(seq->data[i][j]);
        }
        free(seq->data[i]); // Important !!!
    }
    free(seq->data);
    free(seq);
}

// seq_insert_at(seq, data, r, c) inserts data at given row and column
//  data will be replaced if such position already contains an element
// Effects: mutates *seq
// Requires: seq is not NULL, 0 <= r < row, 0 <= c < col
// Time: O(k)

void seq_insert_at(struct Sequence* seq, void* data, const int r, const int c) {
    seq->destroy(seq->data[r][c]);
    seq->data[r][c] =  data;
}

// seq_remove_at(seq, r, c) removes and returns the data at given row and column
//  returns NULL if no element is at such position
// Effects: may mutate *seq
// Requires: seq is not NULL, 0 <= r < row, 0 <= c < col
// Time: O(k)

void* seq_remove_at(struct Sequence* seq, const int r, const int c) {
    void* temp = seq->data[r][c]; 
    seq->data[r][c] = NULL;
    return temp;
}

// seq_at(seq, r, c) returns the data at given row and column
//  returns NULL if no element is at such position
// Requires: seq is not NULL, 0 <= r < row, 0 <= c < col
// Time: O(1)

void* seq_at(const struct Sequence* seq, const int r, const int c) {
    return seq->data[r][c];
}

// seq_print(seq) prints the seq row by row
// Time: O(r * c * k) where O(k) is print

void seq_print(const struct Sequence* seq) {
    for (int i = 0; i < seq->row; i++) {
        for (int j = 0; j < seq->column; j++) {
            seq->print(seq->data[i][j]);
        }
    }
}
