#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

bool areAllLetters(string key);

bool thereAreDuplicates(string key);

int main(int argc, string argv[])
{
    string key;

    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else if (!areAllLetters(argv[1]))
    {
        printf("Key must contains only letters.\n");
        return 1;
    }
    else if (!thereAreDuplicates(argv[1]))
    {
        printf("Key musn't contains duplicate characters.\n");
        return 1;
    }
    else
    {
        key = argv[1];
    }

    string plainText = get_string("plaintext: ");

    printf("ciphertext: ");

    for (int i = 0, n = strlen(plainText); i < n; i++)
    {
        char c = plainText[i];

        if (c >= 'A' && c <= 'Z')
        {
            c = toupper(key[c - 65]);
        }
        else if (c >= 'a' && c <= 'z')
        {
            c = tolower(key[c - 97]);
        }

        printf("%c", c);
    }

    printf("\n");

    return 0;
}

bool areAllLetters(string key)
{
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        if (key[i] < 'A' || key[i] > 'z' || (key[i] > 'Z' && key[i] < 'a'))
        {
            return false;
        }
    }
    return true;
}

bool thereAreDuplicates(string key)
{
    int len = strlen(key);

    int charCount;

    for (int i = 0; i < len; i++)
    {
        charCount = 0;

        for (int j = 0; j < len; j++)
        {
            if (key[i] == key[j])
            {
                charCount++;

                if (charCount > 1)
                {
                    return false;
                }
            }
        }
    }

    return true;
}