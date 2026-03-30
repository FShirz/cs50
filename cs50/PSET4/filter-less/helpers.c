#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // define each variable
    int redmain, greenmain, bluemain;
    float grayout;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            redmain = image[i][j].rgbtRed;
            greenmain = image[i][j].rgbtGreen;
            bluemain = image[i][j].rgbtBlue;

            // calculate grayout
            grayout = round((redmain + greenmain + bluemain) / 3.0);

            // replace each pixel with grayout
            image[i][j].rgbtRed = grayout;
            image[i][j].rgbtGreen = grayout;
            image[i][j].rgbtBlue = grayout;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // define each variable
    int originalRed, originalGreen, originalBlue;
    int sepiaRed, sepiaGreen, sepiaBlue;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            originalRed = image[i][j].rgbtRed;
            originalGreen = image[i][j].rgbtGreen;
            originalBlue = image[i][j].rgbtBlue;

            // calculate sepia
            sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            // replace each pixel with sepia filtered one
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // define each variable
    RGBTRIPLE rowplace[width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            rowplace[j] = image[i][j];
        }
        for (int j = 0; j < width; j++)
        {
            // replace each pixel with its reflect
            image[i][j].rgbtRed = rowplace[width - j - 1].rgbtRed;
            image[i][j].rgbtGreen = rowplace[width - j - 1].rgbtGreen;
            image[i][j].rgbtBlue = rowplace[width - j - 1].rgbtBlue;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // define each variable
    RGBTRIPLE copy[height][width];

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            copy[h][w] = image[h][w];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int counter = 0;
            float redsum = 0;
            float greensum = 0;
            float bluesum = 0;

            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if (!(i + k < 0 || i + k >= height || j + l < 0 || j + l >= width))
                    {
                        redsum += copy[i + k][j + l].rgbtRed;
                        greensum += copy[i + k][j + l].rgbtGreen;
                        bluesum += copy[i + k][j + l].rgbtBlue;
                        counter++;
                    }
                    else
                    {
                        continue;
                    }
                }
            }

            image[i][j].rgbtRed = (int) round(redsum / counter);
            image[i][j].rgbtGreen = (int) round(greensum / counter);
            image[i][j].rgbtBlue = (int) round(bluesum / counter);
        }
    }

    return;
}
