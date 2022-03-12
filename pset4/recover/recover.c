#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage recover imagename");
        return 1;
    }

    FILE *readingFile = fopen(argv[1], "r");

    if (readingFile == NULL)
    {
        printf("Cannot open %s", argv[1]);
        return 1;
    }

    fseek(readingFile, 0L, SEEK_END);
    long int fileSize = ftell(readingFile);
    rewind(readingFile);

    long int readedSize = 0;

    FILE *writingFile = NULL;

    int counter = 0;

    BYTE buffer[sizeof(BYTE) * 512];

    while (counter <= 50)
    {
        if ((readedSize + 512) > fileSize)
        {
            break;
        }

        fread(buffer, sizeof(uint8_t), 512, readingFile);

        readedSize += 512;

        if (buffer[0] == 0xFF && buffer[1] == 0xd8 && buffer[2] == 0xff)
        {
            if (buffer[3] == 0xe0 || buffer[3] == 0xe1 || buffer[3] == 0xe2 || buffer[3] == 0xe3 || buffer[3] == 0xe4 || buffer[3] == 0xe5 ||
                buffer[3] == 0xe6 || buffer[3] == 0xe7 || buffer[3] == 0xe8 || buffer[3] == 0xe9 || buffer[3] == 0xea || buffer[3] == 0xeb ||
                buffer[3] == 0xec || buffer[3] == 0xed || buffer[3] == 0xee || buffer[3] == 0xef)
            {
                if (writingFile != NULL)
                {
                    fclose(writingFile);
                }

                char fileName[8];

                sprintf(fileName, "%03d.jpg", counter);

                writingFile = fopen(fileName, "w");

                counter++;
            }
        }

        if (writingFile != NULL)
        {
            fwrite(buffer, sizeof(uint8_t), 512, writingFile);
        }
    }

    fclose(readingFile);
}