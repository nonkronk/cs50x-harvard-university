// Irvan Tristian
// 06 April 2020
// Problem Set 2 - Encrypt messages using Substitution cipher
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 256

// Prototype the functions
char cipherize(string k, char t);
int is_alpha(string a);
int is_duplicate(string a);

// Create global variable for function
int times = 1;

// Main Program
int main(int argc, string argv[])
{
    // Check that the program was run with 1 argument
    if (argc == 2)
    {
        // Check whether the characters are alphabet or not
        if (is_alpha(argv[1]) == 1)
        {
            // Check whether the length of characters are 26
            if (strlen(argv[1]) == 26 && is_duplicate(argv[1]) == -1)
            {
                string text = get_string("plaintext:  ");

                // Print ciphered text
                printf("ciphertext: ");
                for (int i = 0, l = strlen(text); i < l; i++)
                {
                    char r = cipherize(argv[1], text[i]);
                    printf("%c", r);
                }
                printf("\n");
            }
            else
            {
                printf("Key must contain 26 characters.\n");
                return 1;
            }
        }
        else
        {
            printf("Invalid keyword\n");
            return 1;
        }
    }
    else
    {
        printf("Usage: %s keyword\n", argv[0]);
        return 1;
    }
}

// Returns whether the characters are alphabet or not
int is_alpha(string a)
{
    for (int i = 0, l = strlen(a); i < l; i++)
    {
        int c = (int) a[i];
        if (c < 97 && c > 90)
        {
            times = 0;
        }
        else if (c < 65 || c > 122)
        {
            times *= 0;
        }
        else
        {
            times *= 1;
        }
    }
    return times;
}

// Return int wether character are duplicated

int is_duplicate(string s)
{
    // this is optimized method
    int p = -1, i, k;

    // initialized counts of occurrences of
    // elements as zero
    int hash[MAX_CHAR] = { 0 };

    // initialized positions
    int pos[MAX_CHAR];

    for (i = 0; i < strlen(s); i++)
    {
        k = (int)s[i];

        if (hash[k] == 0)
        {
            hash[k]++;
            pos[k] = i;
        }
        else if (hash[k] == 1)
        {
            hash[k]++;
        }
    }

    for (i = 0; i < MAX_CHAR; i++)
    {
        if (hash[i] == 2)
        {
            if (p == -1) // base case
            {
                p = pos[i];
            }
            else if (p > pos[i])
            {
                p = pos[i];
            }
        }
    }

    return p;
}

// Returns a ciphered char
char cipherize(string k, char t)
{
    if (t >= 65 && t <= 90)
    {
        int int_t = (int) t;
        int_t -= 65;
        int int_k = (int) k[int_t];
        if (int_k >= 97 && int_k <= 122)
        {
            int_k -= 32;
            t = (char) int_k;
        }
        else
        {
            t = k[int_t];
        }
        return t;
    }
    else if (t >= 97 && t <= 122)
    {
        int int_t = (int) t;
        int_t -= 97;
        int int_k = (int) k[int_t];
        if (int_k >= 97 && int_k <= 122)
        {
            t = k[int_t];
        }
        else
        {
            int_k += 32;
            t = (char) int_k;
        }
        return t;
    }
    else
    {
        return t;
    }
}