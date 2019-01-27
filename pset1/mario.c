// PSET1 - Recreate Mario World 1-1 pyramids in C
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // define local variable within main, named height
    int height;
    
    // Get height input from the user
    do
    {
        height = get_int("Height: ");
    }
    while (height <= 0 || height > 8);
    
    // Create the pyramid
    for (int i = 0; i < height; i++)
    {
        for (int j = height - 1; j > i; j--)
        {
            printf(" ");
        }
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        printf("  ");
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}
