// Implements a dictionary's functionality
#include <string.h>
#include <strings.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "dictionary.h"

int wordsdictcount = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 1500;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    unsigned int h = hash(word);

    node *n = table[h];

    while (n != NULL)
    {
        //if (areequals(word, n->word))
        if (strcasecmp(word, n->word) == 0)
        {
            return true;
        }
        else
        {
            n = n->next;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int sum = 0;

    for (int i = 0, length = strlen(word); i < length; i++)
    {
        sum += (int)tolower(word[i]);
    }

    //printf("word %s / hash=%d\n\n", word, sum % N);

    return sum % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");

    if (file == NULL)
    {
        printf("Could not load %s\n", dictionary);
        return false;
    }

    int index = 0;

    char word[LENGTH + 1];

    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    for (int c = fgetc(file); c != EOF; c = fgetc(file))
    {
        if (isalpha(c) || (c == '\'' && index > 0))
        {
            word[index] = c;
            index++;

            if (index > LENGTH)
            {
                while ((c = fgetc(file) != EOF && isalpha(c)));

                index = 0;
            }
        }
        else if (isdigit(c))
        {
            while ((c = fgetc(file) != EOF && isalpha(c)));

            index = 0;
        }
        else if (index > 0)
        {
            word[index] = '\0';

            unsigned int h = hash(word);

            node *n = malloc(sizeof(node));

            for (int i = 0, l = strlen(word); i <= l; i++)
            {
                n->word[i] = word[i];
                n->next = NULL;
            }

            if (table[h] != NULL)
            {
                n->next = table[h];
            }

            table[h] = n;

            index = 0;

            wordsdictcount += 1;
        }
    }

    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return wordsdictcount;
}

void freenode(node *n)
{
    if (n != NULL)
    {
        if (n->next != NULL)
        {
            freenode(n->next);
        }
    }

    free(n);
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            freenode(table[i]);
        }
    }

    return true;
}