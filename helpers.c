#include "helpers.h"
#include "math.h"
#include "ctype.h"


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // iterate through height and width of 2d array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // find average of RGB values and make them the same, lower number is darker
            int avg = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // nested loops iterating through each pixel again
    for (int k = 0; k < height; k++)
    {
        for (int l = 0; l < width; l++)
        {
            int sepiaRed = round((image[k][l].rgbtRed * 0.393) + (image[k][l].rgbtGreen * 0.769) + (image[k][l].rgbtBlue * 0.189));
            // RGB value caps at 255, maybe there's a better way than using a conditional, like a function for the math
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            int sepiaGreen = round((image[k][l].rgbtRed * 0.349) + (image[k][l].rgbtGreen * 0.686) + (image[k][l].rgbtBlue * 0.168));
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            int sepiaBlue = round((image[k][l].rgbtRed * 0.272) + (image[k][l].rgbtGreen * 0.534) + (image[k][l].rgbtBlue * 0.131));
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            // changing pixel to sepia color
            image[k][l].rgbtRed = sepiaRed;
            image[k][l].rgbtGreen = sepiaGreen;
            image[k][l].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int m = 0; m < height; m++)
    {
        // don't reflect in half, need to use pointers
        for (int n = 0; n < width / 2; n++)
        {
            // tmp = pointer to pixel, or image[m][n]
            // tmp = *a
            // *a = *b
            // *b = tmp
            RGBTRIPLE tmp = image[m][n];
            RGBTRIPLE tmp2 = image[m][(width - 1) - n];
            image[m][(width - 1) - n] = tmp;
            image[m][n] = tmp2;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // make a copy so blurred pixels don't affect next blur
    RGBTRIPLE copy[height][width];
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            copy[x][y] = image[x][y];
        }
    }

    // looping through each pixel in the copy
    for (int o = 0; o < height; o++)
    {

        for (int p = 0; p < width; p++)
        {

            // divisor is float for implicit conversion to round
            float count = 0.0;
            int blur_red = 0;
            int blur_green = 0;
            int blur_blue = 0;


            for (int q = -1; q < 2; q++)
            {
                // from image[][r - 1 to r + 1]
                for (int r = -1; r < 2; r++)
                {
                    // how to check if pixel is valid? four inequalities
                    // height + q greater than 0, less than height -1
                    // width + q greater than 0, less than width -1
                    if ((o + q >= 0) && (o + q <= height - 1) && (p + r >= 0) && (p + r <= width - 1))
                    {
                        // add valid pixel rgb values to variable
                        blur_red += copy[o + q][p + r].rgbtRed;
                        blur_green += copy[o + q][p + r].rgbtGreen;
                        blur_blue += copy[o + q][p + r].rgbtBlue;
                        // add one more to divisor
                        count++;
                    }
                }
            }


            // change image, not copy
            image[o][p].rgbtRed = round(blur_red / count);
            image[o][p].rgbtGreen = round(blur_green / count);
            image[o][p].rgbtBlue = round(blur_blue / count);
        }
    }
    return;
}
