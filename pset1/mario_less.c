// Irvan Tristian
// 19 January 2019
// Problem Set 1 - Recreate Mario World 1-1 pyramid in C
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Define local variable within main, named height
    int height;
    
    // Get height input from the user
    do 
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    
    // Create the pyramid
    for (int i = 0; i < height; i++)
    {
        for (int j = height - 1; j > i; j--)
        {
            printf(" ");
        }
        for (int k = 0; k <= i; k++)
        {
            printf("#");
        }
        printf("\n");
    }
}
