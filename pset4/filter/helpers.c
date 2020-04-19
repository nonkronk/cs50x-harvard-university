#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate over height of image
    for (int i = 0; i < height; i++)
    {
        // Iterate over width of image
        for (int j = 0; j < width; j++)
        {
            float a;
            float r = (float) image[i][j].rgbtRed;
            float g = (float) image[i][j].rgbtGreen;
            float b = (float) image[i][j].rgbtBlue;

            // Calculate average color
            a = round((r + g + b) / 3);

            // Change the color to grayscale
            image[i][j].rgbtRed = (int) a;
            image[i][j].rgbtGreen = (int) a;
            image[i][j].rgbtBlue = (int) a;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate over height of image
    for (int i = 0; i < height; i++)
    {
        // Iterate over width of image
        for (int j = 0; j < width; j++)
        {
            float a;
            float r = (float) image[i][j].rgbtRed;
            float g = (float) image[i][j].rgbtGreen;
            float b = (float) image[i][j].rgbtBlue;

            // Calculate with sefia formula
            r = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            g = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            b = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            // Cap color at 255
            if (r > 255)
            {
                r = 255;
            }
            if (g > 255)
            {
                g = 255;
            }
            if (b > 255)
            {
                b = 255;
            }

            // Change the color to sefia
            image[i][j].rgbtRed = (int) r;
            image[i][j].rgbtGreen = (int) g;
            image[i][j].rgbtBlue = (int) b;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Temporary storage
    RGBTRIPLE temp;

    // Iterate over height of image
    for (int i = 0; i < height; i++)
    {
        // Swap array
        int j = 0, k = width - 1;
        while (j < k)
        {
            temp = image[i][j];
            image[i][j] = image[i][k];
            image[i][k] = temp;
            j++;
            k--;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Temporary store
    RGBTRIPLE ori_img[height][width];

    // Iterate to save entire array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            ori_img[i][j] = image[i][j];
        }
    }

    // Iterate entire array to write blur color
    for (int i = 0, r, g, b, counter; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            r = g = b = counter = 0;

            // Center check
            if (i >= 0 && j >= 0)
            {
                r += ori_img[i][j].rgbtRed;
                g += ori_img[i][j].rgbtGreen;
                b += ori_img[i][j].rgbtBlue;
                counter++;
            }
            // Left check
            if (i >= 0 && j - 1 >= 0)
            {
                r += ori_img[i][j - 1].rgbtRed;
                g += ori_img[i][j - 1].rgbtGreen;
                b += ori_img[i][j - 1].rgbtBlue;
                counter++;
            }
            // Bottom check
            if ((i >= 0 && j + 1 >= 0) && (i >= 0 && j + 1 < width))
            {
                r += ori_img[i][j + 1].rgbtRed;
                g += ori_img[i][j + 1].rgbtGreen;
                b += ori_img[i][j + 1].rgbtBlue;
                counter++;
            }
            // Top check
            if (i - 1 >= 0 && j >= 0)
            {
                r += ori_img[i - 1][j].rgbtRed;
                g += ori_img[i - 1][j].rgbtGreen;
                b += ori_img[i - 1][j].rgbtBlue;
                counter++;
            }
            // Top-left check
            if (i - 1 >= 0 && j - 1 >= 0)
            {
                r += ori_img[i - 1][j - 1].rgbtRed;
                g += ori_img[i - 1][j - 1].rgbtGreen;
                b += ori_img[i - 1][j - 1].rgbtBlue;
                counter++;
            }
            // Top-right check
            if ((i - 1 >= 0 && j + 1 >= 0) && (i - 1 >= 0 && j + 1 < width))
            {
                r += ori_img[i - 1][j + 1].rgbtRed;
                g += ori_img[i - 1][j + 1].rgbtGreen;
                b += ori_img[i - 1][j + 1].rgbtBlue;
                counter++;
            }
            // Bottom-right check
            if ((i + 1 >= 0 && j >= 0) && (i + 1 < height && j >= 0))
            {
                r += ori_img[i + 1][j].rgbtRed;
                g += ori_img[i + 1][j].rgbtGreen;
                b += ori_img[i + 1][j].rgbtBlue;
                counter++;
            }
            // Bottom-left check
            if ((i + 1 >= 0 && j - 1 >= 0) && (i + 1 < height && j - 1 >= 0))
            {
                r += ori_img[i + 1][j - 1].rgbtRed;
                g += ori_img[i + 1][j - 1].rgbtGreen;
                b += ori_img[i + 1][j - 1].rgbtBlue;
                counter++;
            }
            // Right check
            if ((i + 1 >= 0 && j + 1 >= 0) && (i + 1 < height && j + 1 < width))
            {
                r += ori_img[i + 1][j + 1].rgbtRed;
                g += ori_img[i + 1][j + 1].rgbtGreen;
                b += ori_img[i + 1][j + 1].rgbtBlue;
                counter++;
            }
            // Change color
            image[i][j].rgbtRed = round(r / (counter * 1.0));
            image[i][j].rgbtGreen = round(g / (counter * 1.0));
            image[i][j].rgbtBlue = round(b / (counter * 1.0));
        }
    }
    return;
}