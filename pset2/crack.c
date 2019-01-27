// Irvan Tristian
// 27 January 2019
// Problem Set 2 - Brute force DES encryption
#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <cs50.h>

// Prototype function
bool compare_hash(char *hash, char *guess, char *salt);

// Main program
int main(int argc, string argv[])
{
    // Program should accept one and only one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }

    // Define hash and salt
    char *hash = argv[1];
    char salt[3];
    salt[0] = argv[1][0];
    salt[1] = argv[1][1];
    salt[2] = '\0';

    // Define 52 characters from ASCII to generate all possible password (A-Z, a-z)
    int len_chars = 52;
    char chars[len_chars];
    for (int i = 0, A = 65, a = 97; i < 26; i++)
    {
        chars[i] = (char) A + i;
        chars[i + 26] = (char) a + i;
    }

    // Define password length
    char pwd1[2];
    pwd1[1] = '\0';
    char pwd2[3];
    pwd2[2] = '\0';
    char pwd3[4];
    pwd3[3] = '\0';
    char pwd4[5];
    pwd4[4] = '\0';
    char pwd5[6];
    pwd5[5] = '\0';

    // Guess 1 password length
    for (int i = 0; i < len_chars; i++)
    {
        pwd1[0] = chars[i];
        if (compare_hash(hash, pwd1, salt) == true)
        {
            return 0;
        }
    }

    // Guess 2 password length
    for (int i = 0; i < len_chars; i++)
    {
        for (int j = 0; j < len_chars; j++)
        {
            pwd2[0] = chars[i];
            pwd2[1] = chars[j];
            if (compare_hash(hash, pwd2, salt) == true)
            {
                return 0;
            }
        }
    }

    // Guess 3 password length
    for (int i = 0; i < len_chars; i++)
    {
        for (int j = 0; j < len_chars; j++)
        {
            for (int k = 0; k < len_chars; k++)
            {
                pwd3[0] = chars[i];
                pwd3[1] = chars[j];
                pwd3[2] = chars[k];
                if (compare_hash(hash, pwd3, salt) == true)
                {
                    return 0;
                }
            }
        }
    }

    // Guess 4 password length
    for (int i = 0; i < len_chars; i++)
    {
        for (int j = 0; j < len_chars; j++)
        {
            for (int k = 0; k < len_chars; k++)
            {
                for (int l = 0; l < len_chars; l++)
                {
                    pwd4[0] = chars[i];
                    pwd4[1] = chars[j];
                    pwd4[2] = chars[k];
                    pwd4[3] = chars[l];
                    if (compare_hash(hash, pwd4, salt) == true)
                    {
                        return 0;
                    }
                }
            }
        }
    }

    // Guess 5 password length
    for (int i = 0; i < len_chars; i++)
    {
        for (int j = 0; j < len_chars; j++)
        {
            for (int k = 0; k < len_chars; k++)
            {
                for (int l = 0; l < len_chars; l++)
                {
                    for (int m = 0; m < len_chars; m++)
                    {
                        pwd5[0] = chars[i];
                        pwd5[1] = chars[j];
                        pwd5[2] = chars[k];
                        pwd5[3] = chars[l];
                        pwd5[4] = chars[m];
                        if (compare_hash(hash, pwd5, salt) == true)
                        {
                            return 0;
                        }
                    }
                }
            }
        }
    }

    // In case all possible chars doesn't match
    printf("Hash cannot be cracked\n");
    return 0;
}

// Compare hash with guess
bool compare_hash(char *hash, char *guess, char *salt)
{
    char *crypted = crypt(guess, salt);
    if (strcmp(hash, crypted) == 0)
    {
        printf("%s\n", guess);
        return true;
    }
    return false;
}
