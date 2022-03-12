#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    unsigned long creditCardNumber = get_long("Credit card: ");

    //i have to keep the origial credit card number because i wil change the value of creditCardNumber in code
    unsigned long originalCreditCardNumber = creditCardNumber;

    int sumOfDigitsThatWasMultipliedByTwo = 0;

    int sumOfOtherDigits = 0;

    int countOfDigits = 0;

    int product = 0;

    int currentDigit = 0;

    while (creditCardNumber > 0)
    {
        countOfDigits++;

        //Using the logic that Brian have explained
        currentDigit = creditCardNumber % 10;

        //if modulo returns zero, i am in a second-to-last digit
        if (countOfDigits % 2 == 0)
        {
            product = (currentDigit * 2);

            //this loop sum the digits of the product
            while (product > 0)
            {
                sumOfDigitsThatWasMultipliedByTwo += product % 10;

                product /= 10;
            }
        }
        else
        {
            sumOfOtherDigits += currentDigit;
        }

        //this is a important section of code. Here i am making(?) a integer division that will ignore the decimal part.
        //this means that the second-to-last digit now is the last one, so i can repeat the loop logic again
        creditCardNumber /= 10;
    }

    //this divisor will be used to discovery the two first digits of the credit card number
    long divisor = pow(10, (countOfDigits - 2));

    int twoInitialDigits = originalCreditCardNumber / divisor;

    int firstDigit = twoInitialDigits / 10;

    bool valid = ((sumOfDigitsThatWasMultipliedByTwo + sumOfOtherDigits) % 10) == 0;

    if (!valid)
    {
        printf("INVALID\n");
    }
    else if (countOfDigits == 15 && (twoInitialDigits == 34 || twoInitialDigits == 37))
    {
        printf("AMEX\n");
    }
    else if (countOfDigits == 16 && (twoInitialDigits == 51 || twoInitialDigits == 52 || twoInitialDigits == 53
                                     || twoInitialDigits == 54 || twoInitialDigits == 55))
    {
        printf("MASTERCARD\n");
    }
    else if ((countOfDigits == 13 || countOfDigits == 16) && (firstDigit == 4))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}