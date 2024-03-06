#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average_color = round((image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3.0);
            image[i][j].rgbtRed = average_color;
            image[i][j].rgbtGreen = average_color;
            image[i][j].rgbtBlue = average_color;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE buffer[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Calculate the sepia values
            int sepiaRed   = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaBlue  = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            //Clamp the sepia values
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            //Set the sepia values
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
    RGBTRIPLE buffer[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            buffer[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = buffer[i][width - j - 1].rgbtRed;
            image[i][j].rgbtGreen = buffer[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtBlue = buffer[i][width - j - 1].rgbtBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a buffer of the image.
    RGBTRIPLE buffer[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            buffer[i][j] = image[i][j];
        }
    }
    // Blur the image.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avgc[3] = {0, 0, 0};
            int n = 0;
            // Get the average of the surrounding pixels.
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    //Checks if the index is not out of the image so it can add the pixel to the average
                    if ((i + k) >= 0 && (j + l) >= 0 && (i + k) < height && (j + l) < width)
                    {
                        avgc[0] += buffer[i + k][j + l].rgbtRed;
                        avgc[1] += buffer[i + k][j + l].rgbtGreen;
                        avgc[2] += buffer[i + k][j + l].rgbtBlue;
                        n++;
                    }
                }
            }

            // Set the pixel's color to the average.
            image[i][j].rgbtRed = round((avgc[0] / (float)n));
            image[i][j].rgbtGreen = round((avgc[1] / (float)n));
            image[i][j].rgbtBlue = round((avgc[2] / (float)n));
        }
    }
}