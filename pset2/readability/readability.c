// Irvan Tristian
// 05 April 2020
// Problem Set 2 - Computes the Coleman-Liau index of the text

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Prototyping function
int count_letters(string s);
int count_words(string s);
int count_sentences(string s);
float cl_index(float l, float w, float s);

// Main Program
int main()
{
    string text = get_string("Text: ");
    int letter = count_letters(text);
    int word = count_words(text);
    int sentence = count_sentences(text);
    int grade = cl_index(letter, word, sentence);

    /*
    printf("%d letter(s)\n", letter);
    printf("%d word(s)\n", word);
    printf("%d sentence(s)\n", sentence);
    */

    // print grade
    if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %d\n", grade);
    }
}

// count letters
int count_letters(string s)
{
    int count = 0;
    for (int i = 0, l = strlen(s); i < l; i++)
    {
        int c = (int) s[i];
        if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
        {
            count++;
        }
    }
    return count;
}

// count words
int count_words(string s)
{
    int count = 0;
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (s[i] == ' ')
        {
            count++;
        }
    }
    return count + 1;
}

// count sentences
int count_sentences(string s)
{
    int count = 0;
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (s[i] == '.' || s[i] == '!' || s[i] == '?')
        {
            count++;
        }
    }
    return count;
}

// Coleman-Liau index formula
float cl_index(float l, float w, float s)
{
    float la = 100 / w * l;
    float sa = 100 / w * s;

    float index = (0.0588 * la) - (0.296 * sa) - 15.8;
    index = round(index);

    return index;
}