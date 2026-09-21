#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// add your include here


// ================= DO NOT CHANGE THESE LINES =================
typedef int  (*Compare)   (const void*, const void*);
typedef bool (*Predicate) (const void*, const void*);
// =============================================================


// filter_greater_sort(arr, len, size, data, compare)
//  modifies arr by only keeping and sorting elements that are strictly greater than data
//  returns the new length of arr
// Effects: mutates arr
// Time: O(n log n)
int filter_greater_sort(void* arr, int len, int size, const void* data, Compare compare) {
    int count = 0;

    for (int i = 0; i < len; i++) {
        if (compare(arr[i], data) > 0) {
            memcpy(arr + count * size, arr + i * size, size);
            count++;
        }
    }

    qsort(arr, count, size, compare);
    return count;
}

int bsearch_helper(int arr, int len, int data) {
    int left = 0;
    int right = len - 1;

    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == data) {
            return 1;
        } else if (arr[mid] < data) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;
}

// find_index(arr, len, size, data, compare)
//  returns the index of data in arr if exists, otherwise returns -1
// Time: O(log n)
int find_index(const void* arr, int len, int size, const void* data, Compare compare) {
    void* result = bsearch(arr, data, len, size, compare);
    if (result == NULL) {
        return -1;
    } 
    return (result - arr) / size;
}


// and_map(arr, len, size, pred)
//  returns true if every two consecutive elements in the array meet the condition for pred
// Time: O(n)
bool and_map(const void* arr, int len, int size, Predicate pred) {

    for (int i = 0; i < len - 1; i++) {
        if (!pred(arr + i * size, arr + (i + 1) * size)) {
            return false;
        }
    }   

    return true;
}

static cmp_int(const void* v1, const void* v2) {
    const int* i1 = v1;
    const int* i2 = v2;

    if (*v1 % 2 = *v1 % 2) {
        return *v1 - *v2;
    } 
    return (*v1 % 2);
}

// even_before_odd(arr, len)
//  sorts arr by meeting the following criteria:
//  1. all integers are sorted in ascending orders
//  2. all even integers are before all odd integers
// Time: O(n log n)
void even_before_odd(void* arr, int len) {
    qsort(arr, len, sizeof(int), cmp_int);
}


// deep_copy_arr(arr, len, size)
//  returns a new array that contains exactly the same data as arr
// Effects: allocates memory
// Time: O(n)
void* deep_copy_arr(const void* arr, int len, int size) {
    void* new_arr = malloc(size * len);
    
    memcpy(new_arr, arr, size * len);

    return new_arr;
}

int main(void) {
    // Test your code here
}
