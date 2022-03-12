#include "helpers.h"
#include "math.h"
#include "stdio.h"

enum Colors {Red = 0, Green = 1, Blue = 2};

int GxKernel[3][3] = { {-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1} };

int GyKernel[3][3] = { {-1, -2, -1}, {0, 0, 0}, {1, 2, 1} };

void blackAndWith(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            if (image[h][w].rgbtBlue < 127)
            {
                image[h][w].rgbtBlue = 0;
                image[h][w].rgbtGreen = 0;
                image[h][w].rgbtRed = 0;
            }
            else
            {
                image[h][w].rgbtBlue = 255;
                image[h][w].rgbtGreen = 255;
                image[h][w].rgbtRed = 255;
            }
        }
    }
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int avg = round(((float)image[h][w].rgbtBlue + (float)image[h][w].rgbtGreen + (float)image[h][w].rgbtRed) / 3);

            image[h][w].rgbtBlue = avg;
            image[h][w].rgbtGreen = avg;
            image[h][w].rgbtRed = avg;
        }
    }

    //blackAndWith(height, width, image);
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE originalImage[height][width];

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            originalImage[h][w] = image[h][w];
        }
    }

    for (int h = 0; h < height; h++)
    {
        int oppositeColumn = width - 1;

        for (int w = 0; w < width; w++)
        {
            image[h][w] = originalImage[h][oppositeColumn];
            oppositeColumn--;
        }
    }
}

int calcAvgForSurroundingPixels(int height, int width, RGBTRIPLE image[height][width], int currentRow, int currentColumn,
                                enum Colors color)
{
    int sum = 0;

    int count = 0;

    for (int h = currentRow - 1; h <= (currentRow + 1); h++)
    {
        for (int w = currentColumn - 1; w <= (currentColumn + 1); w++)
        {
            if (h > -1 && h < height && w > -1 && w < width)
            {
                if (color == Blue)
                {
                    sum += image[h][w].rgbtBlue;
                }
                else if (color == Green)
                {
                    sum += image[h][w].rgbtGreen;
                }
                else if (color == Red)
                {
                    sum += image[h][w].rgbtRed;
                }
                count++;
            }
        }
    }

    return round((float)sum / (float)count);
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE originalImage[height][width];

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            originalImage[h][w] = image[h][w];
        }
    }

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w].rgbtBlue = calcAvgForSurroundingPixels(height, width, originalImage, h, w, Blue);
            image[h][w].rgbtGreen = calcAvgForSurroundingPixels(height, width, originalImage, h, w, Green);
            image[h][w].rgbtRed = calcAvgForSurroundingPixels(height, width, originalImage, h, w, Red);
        }
    }
}

int calcGx(int height, int width, RGBTRIPLE image[height][width], int currentRow, int currentColumn, enum Colors color)
{
    int sum = 0;

    for (int h = currentRow - 1; h <= (currentRow + 1); h++)
    {
        for (int w = currentColumn - 1; w <= (currentColumn + 1); w++)
        {
            int x = w - currentColumn + 1;

            int y = h - currentRow + 1;

            if (h > -1 && h < height && w > -1 && w < width)
            {
                if (color == Blue)
                {
                    sum += image[h][w].rgbtBlue * GxKernel[x][y];
                }
                else if (color == Green)
                {
                    sum += image[h][w].rgbtGreen * GxKernel[x][y];;
                }
                else if (color == Red)
                {
                    sum += image[h][w].rgbtRed * GxKernel[x][y];;
                }
            }
        }
    }

    return sum;
}

int calcGy(int height, int width, RGBTRIPLE image[height][width], int currentRow, int currentColumn, enum Colors color)
{
    int sum = 0;

    for (int h = currentRow - 1; h <= (currentRow + 1); h++)
    {
        for (int w = currentColumn - 1; w <= (currentColumn + 1); w++)
        {
            int x = w - currentColumn + 1;

            int y = h - currentRow + 1;

            if (h > -1 && h < height && w > -1 && w < width)
            {
                if (color == Blue)
                {
                    sum += image[h][w].rgbtBlue * GyKernel[x][y];
                }
                else if (color == Green)
                {
                    sum += image[h][w].rgbtGreen * GyKernel[x][y];;
                }
                else if (color == Red)
                {
                    sum += image[h][w].rgbtRed * GyKernel[x][y];;
                }
            }
        }
    }

    return sum;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE originalImage[height][width];

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            originalImage[h][w] = image[h][w];
        }
    }

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int blue = round(sqrt((float)pow(calcGx(height, width, originalImage, h, w, Blue), 2) + (float)pow(calcGy(height, width,
                                  originalImage, h, w, Blue), 2)));
            int green = round(sqrt((float)pow(calcGx(height, width, originalImage, h, w, Green), 2) + (float)pow(calcGy(height, width,
                                   originalImage, h, w, Green), 2)));
            int red = round(sqrt((float)pow(calcGx(height, width, originalImage, h, w, Red), 2) + (float)pow(calcGy(height, width,
                                 originalImage, h, w, Red), 2)));

            if (blue > 255)
            {
                blue = 255;
            }

            if (green > 255)
            {
                green = 255;
            }

            if (red > 255)
            {
                red = 255;
            }

            image[h][w].rgbtBlue = blue;
            image[h][w].rgbtGreen = green;
            image[h][w].rgbtRed = red;
        }
    }
}
