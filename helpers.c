#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            // Iterate through each pixel, replacing RGB values with average
            int avg = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j] = (RGBTRIPLE)
            {
                avg, avg, avg
            };
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            // Given sepia conversion algorithm
            int sepiaRed = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);

            // 255 8-bit color cap
            image[i][j].rgbtRed = sepiaRed > 255 ? 255 : sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen > 255 ? 255 : sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue > 255 ? 255 : sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width / 2; ++j)
        {
            // make copies of current and last
            RGBTRIPLE curr = image[i][j];
            RGBTRIPLE next = image[i][width - 1 - j];
            // switch
            image[i][j] = next;
            image[i][width - 1 - j] = curr;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    // creating a copy so blurs don't overlap
    RGBTRIPLE copy[height][width];
    memcpy(copy, image, sizeof(RGBTRIPLE) * height * width);

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            // number of valid pixels, float to round division
            float c = 0.0;

            // sum of pixels around
            int blurRed = 0, blurGreen = 0, blurBlue = 0;

            // iterate in a 3x3 around curr
            for (int k = -1; k < 2; ++k)
            {
                for (int l = -1; l < 2; ++l)
                {
                    // current pixel postion to validate
                    int row = i + k, col = l + j;
                    // check if within boundaries
                    if ((row >= 0) && (row <= height - 1) && (col >= 0) && (col <= width - 1))
                    {
                        blurRed += copy[row][col].rgbtRed;
                        blurGreen += copy[row][col].rgbtGreen;
                        blurBlue += copy[row][col].rgbtBlue;
                        ++c;
                    }
                }
            }
            image[i][j] = (RGBTRIPLE)
            {
                round(blurBlue / c), round(blurGreen / c), round(blurRed / c)
            };
        }
    }
    return;
}
