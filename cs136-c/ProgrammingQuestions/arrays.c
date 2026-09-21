#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
// add your include here


// ================= DO NOT CHANGE THESE LINES =================
typedef bool (*Predicate) (const void*);
// =============================================================


// shrink_array(arr, len, pred)
//  removes elements from arr that do not meeting the condition for pred
// Effects: may mutate *arr and *len
// Time: O(n)
void shrink_array(int** arr, int* len, Predicate pred) {
    assert(arr);
    assert(*len > 0);

    int count = 0;
    for (int i = 0; i < *len; i++) {
        if (pred((*arr)[i])) {
            (*arr)[count] = (*arr)[i];
            count += 1;
        }
    }

    *len = count;
    *arr = realloc(*arr, sizeof(int) * *len);
}


// insert_k(arr, len, k)
//  inserts k into the middle of every consecutive elemnts in arr
//  returns the new length of arr
// Effects: mutates *arr
// Time: O(n)
int insert_k(int* arr, int len, int k) {
    int cap = len;

    *arr = realloc(*arr, sizeof(int) * len);

    if(len <= 1) {
        return len;
    }

    for (int i = len - 1; i >= 0; i--) {
        arr[i * 2] = arr[i];
    }

    for (int i = 1; i < 2 * len; i += 2) {
        arr[i] = k;
    }

    return 2 * len - 1;
}


// addition(arr1, len1, arr2, len2, len)
//  returns a new array by adding arr1 and arr2
// Effects: allocates memory, mutates* len
// Time: O(n)
int* addition(const int* arr1, int len1, const int* arr2, int len2, int* len) {
    int temp = 0;
    int count = 0;

    int len = len2 + 1;
    if (len1 > len2) {
        len = len1 + 1;
    }
    int* arr = malloc(sizeof(int) * len);

    while (count < len1 && count < len2) {
        int num1 = arr1[len1 - 1 - count];
        int num2 = arr2[len2 - 1 - count];

        arr[count] = (num1 + num2) % 10;
        temp = (num1 + num2) % 10;
        count ++;
    }

    while (count < len1) {
        arr[count] = (arr1[len1 - 1 - count] + temp) % 10;
        temp = (arr1[len1 - 1 - count] + temp) / 10;
        count++;
    }

    while (count < len2) {
        arr[count] = (arr2[len2 - 1 - count] + temp) % 10;
        temp = (arr2[len2 - 1 - count] + temp) / 10;
        count++;
    }
    
    *len = count;
    int* reverse_arr = malloc(sizeof(int) * count);
    for (int i = 0; i < *len; i++) {
        reverse_arr[i] = arr[*len - 1 - i];
    } 

    free(arr);
    return reverse_arr;
}


// pascal_triangle_row(n, len)
//  returns the nth row of pascal triangle
// Effects: allocates memory, mutates *len
// Time: O(n^2)
int* pascal_triangle_row(int n, int* len) {
    assert(n >= 1);

    int* arr = malloc(sizeof(int) * len);
    arr[0] = 1;
    arr[len - 1] = 1;

    for (int i = 2; i < len; i++) {
        for (int j = 1; j < len - 1; j++) {
            arr[j] = arr[j] + arr[j - 1]; 
        }
    }

    return arr;
}

// dominantIndex(arr, len)
//  returns the index of the largest element 
//  if it is at least twice as much as every other elements in arr, or returns -1 otherwise
// Time: O(n)
int dominantIndex(const int* arr, int len) {
    assert(arr);

    int max = arr[0];
    int index = 0;

    for (int i = 1; i < len; i++) {
        if (arr[i] > max) {
            max = arr[i];
            index = i;
        }
    }

    for (int j = 0; j < len; j++) {
        if (arr[j] * 2 > max) {
            return -1;
        }
    }

    return index;
}

int main(void) {

}
