#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
// add your include here

// print_all(words, len)
//  prints all hidden strings in words, one string per line
// Effects: produces output
// Time: O(n) 
void print_all(const char* words, int len) {
    int count = 0;
    int index = 0;
    while (count < len - 1) {
        if (words[count] == '\0') {
            printf("%s", words + index);
            count += 1;
            index = count + 1;
        }
        count++;
    }
}

void print_all_2nd(const char* words, int len) {
    char prev = '\0';
    for (int i = 0; i < len; i++) {
        if (prev == '\0' && words[i] != '\0') {
            printf("%s", words[i]);
        }
        prev = words[i];
    }
}

// append_all_strings(aos, len)
//  returns a single string by appending all strings in aos
// Effects: allocates memory
// Time: O(mn) where m is the largest length of string in aos
char* append_all_strings(const char** aos, int len) {
    assert(aos);
    assert(len > 0);

    int count = 0;
    int cap = 1;
    char* new_str = malloc(sizeof(char) * cap);

    for (int i = 0; i < len; i++) {
        for (int j = 0; aso[i][j], j++) {
            if (len == cap - 1) {
                cap *= 2;
                realloc(new_str, sizeof(char) * cap);
            }
            new_str[count] = aso[i][j];
            count++;
        }
    }

    new_str[count] = '\0';
    return new_str;
}

// merge_sort_strings(aos, len)
//  sorts aos using merge sort
// Effects: mutates *aos
// Time: O(mn log n) where m is the largest length of string in aos
void merge_sort_strings(char** aos, int len) {
    // your implementation goes here
}

// is_anagram(s1, s2)
//  returns true if s1 and s2 are anagrams, and false otherwise
// Time: O(n)
bool is_anagram(const char* s1, const char* s2) {
    int arr[128] = {0};
    
    for (int i = 0; s1[i]; i++) {
        arr[s1[i]] += 1;
    }

    for (int j = 0; s1[j]; j++) {
        arr[s2[j]] += 1;
    }

    for (int i = 0; i < 128; i++) {
        if (arr[i] != 0) {
            return false;
        }
    }

    return true;
} 

static void create_palindrome_helper(char* str, int* len, int* cap) {
    char ch = '\0';
    if (scanf(" %c", &ch) > 0) {
        if (len == cap - 1) {
            *cap *= 2;
            *str = realloc(*str, sizeof(char) * *cap);
        }

        (*str)[*len] = ch;
        *len += 1;

        create_palindrome_helper(str, len, cap);

        if (len == cap - 1) {
            *cap *= 2;
            *str = realloc(*str, sizeof(char) * *cap);
        }

        (*str)[*len] = ch;
        *len += 1;
    }
}

// create_palindrome()
//  returns a palindrome string by reading from standard input
// Effects: allocates memory
// Time: O(n)
char* create_palindrome(void) {
    int len = 0;
    int cap = 1;
    char* str = malloc(sizeof(char) * cap);

    create_palindrome_helper(str, len, cap);

    return str;
}


char* create_palindrome_iterate(void) {
    int len = 0;
    int cap = 1;
    char* str = malloc(sizeof(char) * cap);
    char c = '\0';

    while (scanf(" %c", &c) > 0) {
        if (len == cap - 1) {
            cap *= 2;
            str = malloc(str, sizeof(char) * cap);
        }

        str[len] = c;
        len += 1;
    }

    for (int i = len - 1; i >= 0; i--) {
        if (len == cap - 1) {
            cap *= 2;
            str = malloc(str, sizeof(char) * cap);
        }

        str[len] = str[i];
        len ++;
    }

    str[len] = '\0';
    return str;
}

int main(void) {

}
