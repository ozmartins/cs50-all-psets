#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float change = 0;

    do
    {
        change = get_float("How much change I owe?\n");
    }
    while (change <= 0);

    int changeInCents = round(change * 100);

    int coins = 0;

    int quotient = 0;

    int divisor = 0;

    while (changeInCents > 0)
    {
        if (changeInCents >= 25)
        {
            divisor = 25;
        }
        else if (changeInCents >= 10)
        {
            divisor = 10;
        }
        else if (changeInCents >= 5)
        {
            divisor = 5;
        }
        else
        {
            divisor = 1;
        }

        quotient = floor(changeInCents / divisor);

        coins += quotient;

        changeInCents -= quotient * divisor;
    }

    printf("%d\n", coins);
}