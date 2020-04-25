// Irvan Tristian
// 19 January 2019
// Problem Set 2 - Encrypt messages using Vigenère’s cipher
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Prototype the functions
char cipherize(string k, char t);
int is_alpha(string a);

// Create global variable for function
int j = 0;
int times = 1;

// Main Program
int main(int argc, string argv[])
{
    // Check that the program was run with 1 argument
    if (argc == 2)
    {    
        if (is_alpha(argv[1]) == 1)
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

// Returns a ciphered char
char cipherize(string a, char b)
{
    // change key char based on length counter
    int k = (int) a[j % sizeof(a)];
    
    // convert to 0-25 number
    if (k >= 65 && k <= 90)
    {
        k -= 65;
    }
    else if (k >= 97 && k <= 122)
    {
        k -= 97;
    }
    
    // repair pattern
    int x = 0;
    if (b >= 65 && b <= 90)
    {
        j++;
        x = 65;
        if (j == strlen(a))
        {
            j = 0;
        }
    }
    else if (b >= 97 && b <= 122)
    {
        j++;
        x = 97;
        if (j == strlen(a))
        {
            j = 0;
        }
    }
    else
    {
        return b;
    }
    
    // calculate cipher
    int p = (int) b;
    p -= x;
    int s = (p + k) % 26;
    char r = (char)(s + x);
    return r;
}
