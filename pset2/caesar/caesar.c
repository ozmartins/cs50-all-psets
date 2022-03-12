#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>

bool argsAreValid(int argc, string argv[]);

int main(int argc, string argv[])
{
    int key = 0;

    if (!argsAreValid(argc, argv))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        key = atoi(argv[1]);
    }

    string plainText = get_string("plaintext: ");

    printf("ciphertext: ");

    for (int i = 0, n = strlen(plainText); i < n; i++)
    {
        char c = plainText[i];

        if (c >= 'A' && c <= 'Z')
        {
            c = ((c + key - 65) % 26) + 65;
        }
        else if (c >= 'a' && c <= 'z')
        {
            c = ((c + key - 97) % 26) + 97;
        }

        printf("%c", c);
    }

    printf("\n");

    return 0;
}

bool isNumber(string digits)
{
    for (int i = 0, n = strlen(digits); i < n; i++)
    {
        if (digits[i] < '0' || digits[i] > '9')
        {
            return false;
        }
    }
    return true;
}

bool argsAreValid(int argc, string argv[])
{
    if (argc != 2)
    {
        return false;
    }
    else if (!isNumber(argv[1]))
    {
        return false;
    }
    else
    {
        return true;
    }
}