// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include "dictionary.h"
//#include "farmhash-c.h"
#include <ctype.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

int dict_size = 0;

// Number of buckets in hash table
// My local post code :p (Indonesia)
const unsigned int N = 40379;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    unsigned int key = hash(word);
    if (table[key] != NULL)
    {
        node *cursor = table[key];
        while (cursor != NULL)
        {
            if (strcasecmp(cursor->word, word) == 0)
            {
                return true;
            }
            else
            {
                cursor = cursor->next;
            }
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // // Implements Google Farm Hash Algorithm
    // // https://github.com/uxcn/farmhash-c
    // uint64_t farmed = farmhash(word, strlen(word));

    // // Combined with Google Jump Consistent Hash Algorithm
    // // https://github.com/delaemon/c-jump
    // return jumphash(farmed, N - 1);

    // Hash function djb2 by Dan Bernstein
    // http://www.cse.yorku.ca/~oz/hash.html
    unsigned long hash = 5381;
    int c;

    while ((c = *word++))
    {
        hash = ((hash << 5) + hash) + tolower(c);
    }

    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *file = fopen(dictionary, "r");
    // Create buffer
    char buffer[LENGTH + 1];
    // Check whether file could be opened or not (false)
    if (file == NULL)
    {
        return false;
    }
    // Populate each word in dictionary
    while (fscanf(file, "%s", buffer) != EOF)
    {
        // Create a new node
        node *n = malloc(sizeof(node));
        // Just to be safe
        if (n == NULL)
        {
            fclose(file);
            return false;
        }
        // Add word in to linked list
        strcpy(n->word, buffer);

        // Hashing the word
        unsigned int index = hash(buffer);

        // Set new node to be first element
        n->next = table[index];
        // Reset "head" to be first element again
        table[index] = n;

        // Count words in the dict
        dict_size++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return dict_size;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Iterate through all bucket
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];

        // Traverse linked list
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            // Freeing node
            free(tmp);
        }
    }
    return true;
}

// // Google Jump Consistent Hash Algorithm
// int jumphash(unsigned long long key, int buckets)
// {
//     long long b = -1;
//     long long j = 0;

//     while (j < ((long long)buckets))
//     {
//         b = j;
//         key = key * 2862933555777941757 + 1;
//         j = ((long long)(((double)(b + 1)) * (((double)(((long long)1) << 31)) / ((double)((key >> 33) + 1)))));
//     }
//     return (int)b;
// }