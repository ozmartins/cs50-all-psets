#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int main(void)
{
    string text = "";

    text = get_string("Text: ");

    int letters = 0;

    int words = 0;

    int sentences = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if ((text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z'))
        {
            letters++;
        }

        if (text[i] == ' ')
        {
            words++;
        }

        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }

    if (text[strlen(text) - 1] != ' ')
    {
        words++;
    }

    float lettersPer100Words = (float)letters / (float)words * 100;

    float sentencesPer100Words = (float)sentences / (float)words * 100;

    float index = 0.0588 * lettersPer100Words - 0.296 * sentencesPer100Words - 15.8;

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", (int)round(index));
    }
}