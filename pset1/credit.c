// Irvan Tristian
// 19 January 2019
// Problem Set 1 - Check whether CC Number is AMEX, MASTERCARD, VISA, or INVALID
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Define local variable within main
    long number;
    
    // Get CC Number input from the user
    do
    {
        number = get_long("Number: ");
    }
    while (number <= 0);
    
    // Define variable for Finding out length of Card Number
    long n = number;
    int len_number = 0;
    
    // Find out length of Card Number
    while (n != 0)
    {
        n /= 10;
        ++len_number;
    }
    
    // Define variable for calculating
    int count = len_number / 2;
    long num_scale = 10;
    int sum = 0;
    int digit0;
    int digit1;
    
    // Calculate from second-to-last digit
    for (int i = 0; i < count; i++)
    {
        long digit = (number / num_scale) % 10;
        int each_sum = digit * 2;
        if (each_sum >= 10)
        {
            each_sum = (each_sum % 10) + 1;
        }
        sum += each_sum;
        if (i == count - 1)
        {
            digit0 = digit;
        }
        num_scale *= 100;
    }
    
    // Redefine few variable for another calculating
    num_scale = 1;
    count = len_number - (len_number / 2);
    
    // Calculate with the sum of the other digits 
    for (int i = 0; i < count; i++)
    {
        long digit = (number / num_scale) % 10;
        sum += digit;
        if (i == count - 1)
        {
            digit1 = digit;
        }
        num_scale *= 100;
    }
    
    // Define variable for validating
    int check = sum % 10;
    
    // Validate last digit in the sum
    if (check == 0)
    {
        switch (len_number)
        {
            case 15:
                if (digit1 == 3)
                {
                    if (digit0 == 4 || digit0 == 7)
                    {
                        printf("AMEX\n");
                    }
                    else
                    {
                        printf("INVALID\n");
                    }
                }
                else
                {
                    printf("INVALID\n");
                }
                break;
                
            case 13:
                if (digit1 == 4)
                {
                    printf("VISA\n");
                }
                else
                {
                    printf("INVALID\n");
                }
                break;
                
            case 16:
                if (digit0 == 4)
                {
                    printf("VISA\n");
                }
                else if (digit0 == 5)
                {
                    if (digit1 >= 1 && digit1 <= 5)
                    {
                        printf("MASTERCARD\n");
                    }
                    else
                    {
                        printf("INVALID\n");
                    }
                }
                else
                {
                    printf("INVALID\n");
                }
                break;
            default:
                printf("INVALID\n");
                break;
        }
    }
    else
    {
        printf("INVALID\n");
    }
}
        

