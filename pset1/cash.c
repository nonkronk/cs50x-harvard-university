// Irvan Tristian
// 19 January 2019
// Problem Set 1 - Check whether CC Number is AMEX, MASTERCARD, VISA, or INVALID
#include <stdio.h>
#include <cs50.h>
#include <math.h>
	
int main(void)
{
    // Define variable for input
    float owed = 0;
    
    // Get user input
    do
    {
        owed = get_float("Change owed: ");
    }
    while (owed < 0);
    
    // Convert owed to int dollars
    int dollars = owed;
    
    // Convert dollars to cents
    int cents = dollars * 100 + round((owed - dollars) * 100);
    
    // Define variable to represent coins used
    int coins = 0;
    
    // Calculate
    while (cents >= 25)
    {
        cents -= 25;
        coins++;
    }
    while (cents >= 10)
    {
        cents -= 10;
        coins++;
    }
    while (cents >= 5)
    {
        cents -= 5;
        coins++;
    }
    while (cents >= 1)
    {
        cents -= 1;
        coins++;
    }
    
    // Print fewest coins possible
    printf("%d\n", coins);
}
