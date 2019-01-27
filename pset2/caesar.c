// Irvan Tristian
// 19 January 2019
// Problem Set 2 - Encrypt messages using Caesar’s cipher
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Prototype the functions
char cipherize(string k, char t);
bool is_digits(string a);

// Main Program
int main(int argc, string argv[])
{
    // Check that the program was run with one command-line argument
    if (argc == 2)
    {    
        if (is_digits(argv[1]))
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
            printf("Usage: ./caesar key\n");
        }
    }
    else
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }
}

// Returns whether the characters are digit or not
bool is_digits(string a)
{
    for (int i = 0, l = strlen(a); i < l; i++)
    {
        int c = (int) a[i];
        if (c < 48 || c > 57)
        {
            return false;
        }
    }
    return true;
}

// Returns a ciphered char
char cipherize(string a, char b)
{
    int x = 0;
    int k = atoi(a);
    int p = (int) b;
    if (b >= 65 && b <= 90)
    {
        x = 65;
    }
    else if (b >= 97 && b <= 122)
    {
        x = 97;
    }
    else
    {
        return b;
    }
    p -= x;
    int c = (p + k) % 26;
    char r = (char)(c + x);
    return r;
}
