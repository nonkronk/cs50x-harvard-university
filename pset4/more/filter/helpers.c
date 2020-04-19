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

            // Center check or 11 position in 3x3 array
            if (i >= 0 && j >= 0)
            {
                r += ori_img[i][j].rgbtRed;
                g += ori_img[i][j].rgbtGreen;
                b += ori_img[i][j].rgbtBlue;
                counter++;
            }
            // Left check or 10 in 3x3 array
            if (i >= 0 && j - 1 >= 0)
            {
                r += ori_img[i][j - 1].rgbtRed;
                g += ori_img[i][j - 1].rgbtGreen;
                b += ori_img[i][j - 1].rgbtBlue;
                counter++;
            }
            // Right check or 12 position in 3x3 array
            if ((i >= 0 && j + 1 >= 0) && (i >= 0 && j + 1 < width))
            {
                r += ori_img[i][j + 1].rgbtRed;
                g += ori_img[i][j + 1].rgbtGreen;
                b += ori_img[i][j + 1].rgbtBlue;
                counter++;
            }
            // Top check or 01 position in 3x3 array
            if (i - 1 >= 0 && j >= 0)
            {
                r += ori_img[i - 1][j].rgbtRed;
                g += ori_img[i - 1][j].rgbtGreen;
                b += ori_img[i - 1][j].rgbtBlue;
                counter++;
            }
            // Top-left check or 00 position in 3x3 array
            if (i - 1 >= 0 && j - 1 >= 0)
            {
                r += ori_img[i - 1][j - 1].rgbtRed;
                g += ori_img[i - 1][j - 1].rgbtGreen;
                b += ori_img[i - 1][j - 1].rgbtBlue;
                counter++;
            }
            // Top-right check or 02 position in 3x3 array
            if ((i - 1 >= 0 && j + 1 >= 0) && (i - 1 >= 0 && j + 1 < width))
            {
                r += ori_img[i - 1][j + 1].rgbtRed;
                g += ori_img[i - 1][j + 1].rgbtGreen;
                b += ori_img[i - 1][j + 1].rgbtBlue;
                counter++;
            }
            // Bottom check or 21 position in 3x3 array
            if ((i + 1 >= 0 && j >= 0) && (i + 1 < height && j >= 0))
            {
                r += ori_img[i + 1][j].rgbtRed;
                g += ori_img[i + 1][j].rgbtGreen;
                b += ori_img[i + 1][j].rgbtBlue;
                counter++;
            }
            // Bottom-left check or 20 position in 3x3 array
            if ((i + 1 >= 0 && j - 1 >= 0) && (i + 1 < height && j - 1 >= 0))
            {
                r += ori_img[i + 1][j - 1].rgbtRed;
                g += ori_img[i + 1][j - 1].rgbtGreen;
                b += ori_img[i + 1][j - 1].rgbtBlue;
                counter++;
            }
            // Bottom check or 22 position in 3x3 array
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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
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

    double r, g, b, x_r, x_g, x_b, y_r, y_g, y_b;
    // Iterate entire array to write blur color
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            x_r = x_g = x_b = y_r = y_g = y_b = 0;
            // Top-left check or 00 position in 3x3 array
            if (i - 1 >= 0 && j - 1 >= 0)
            {
                x_r += -1 * ori_img[i - 1][j - 1].rgbtRed;
                x_g += -1 * ori_img[i - 1][j - 1].rgbtGreen;
                x_b += -1 * ori_img[i - 1][j - 1].rgbtBlue;

                y_r += -1 * ori_img[i - 1][j - 1].rgbtRed;
                y_g += -1 * ori_img[i - 1][j - 1].rgbtGreen;
                y_b += -1 * ori_img[i - 1][j - 1].rgbtBlue;
            }
            // Top check or 01 position in 3x3 array
            if (i - 1 >= 0 && j >= 0)
            {
                x_r += 0;
                x_g += 0;
                x_b += 0;

                y_r += -2 * ori_img[i - 1][j].rgbtRed;
                y_g += -2 * ori_img[i - 1][j].rgbtGreen;
                y_b += -2 * ori_img[i - 1][j].rgbtBlue;
            }
            // Top-right check or 02 position in 3x3 array
            if ((i - 1 >= 0 && j + 1 >= 0) && (i - 1 >= 0 && j + 1 < width))
            {
                x_r += ori_img[i - 1][j + 1].rgbtRed;
                x_g += ori_img[i - 1][j + 1].rgbtGreen;
                x_b += ori_img[i - 1][j + 1].rgbtBlue;

                y_r += -1 * ori_img[i - 1][j + 1].rgbtRed;
                y_g += -1 * ori_img[i - 1][j + 1].rgbtGreen;
                y_b += -1 * ori_img[i - 1][j + 1].rgbtBlue;
            }
            // Left check or 10 in 3x3 array
            if (i >= 0 && j - 1 >= 0)
            {
                x_r += -2 * ori_img[i][j - 1].rgbtRed;
                x_g += -2 * ori_img[i][j - 1].rgbtGreen;
                x_b += -2 * ori_img[i][j - 1].rgbtBlue;

                y_r += 0;
                y_g += 0;
                y_b += 0;
            }
            // Center check or 11 position in 3x3 array
            if (i >= 0 && j >= 0)
            {
                x_r += 0;
                x_g += 0;
                x_b += 0;

                y_r += 0;
                y_g += 0;
                y_b += 0;
            }
            // Right check or 12 position in 3x3 array
            if ((i >= 0 && j + 1 >= 0) && (i >= 0 && j + 1 < width))
            {
                x_r += 2 * ori_img[i][j + 1].rgbtRed;
                x_g += 2 * ori_img[i][j + 1].rgbtGreen;
                x_b += 2 * ori_img[i][j + 1].rgbtBlue;

                y_r += 0;
                y_g += 0;
                y_b += 0;
            }
            // Bottom-left check or 20 position in 3x3 array
            if ((i + 1 >= 0 && j - 1 >= 0) && (i + 1 < height && j - 1 >= 0))
            {
                x_r += -1 * ori_img[i + 1][j - 1].rgbtRed;
                x_g += -1 * ori_img[i + 1][j - 1].rgbtGreen;
                x_b += -1 * ori_img[i + 1][j - 1].rgbtBlue;

                y_r += ori_img[i + 1][j - 1].rgbtRed;
                y_g += ori_img[i + 1][j - 1].rgbtGreen;
                y_b += ori_img[i + 1][j - 1].rgbtBlue;
            }
            // Bottom check or 21 position in 3x3 array
            if ((i + 1 >= 0 && j >= 0) && (i + 1 < height && j >= 0))
            {
                x_r += 0;
                x_g += 0;
                x_b += 0;

                y_r += 2 * ori_img[i + 1][j].rgbtRed;
                y_g += 2 * ori_img[i + 1][j].rgbtGreen;
                y_b += 2 * ori_img[i + 1][j].rgbtBlue;
            }
            // Bottom check or 22 position in 3x3 array
            if ((i + 1 >= 0 && j + 1 >= 0) && (i + 1 < height && j + 1 < width))
            {
                x_r += ori_img[i + 1][j + 1].rgbtRed;
                x_g += ori_img[i + 1][j + 1].rgbtGreen;
                x_b += ori_img[i + 1][j + 1].rgbtBlue;

                y_r += ori_img[i + 1][j + 1].rgbtRed;
                y_g += ori_img[i + 1][j + 1].rgbtGreen;
                y_b += ori_img[i + 1][j + 1].rgbtBlue;
            }

            // Calculate red
            r = (int)round(sqrt((x_r * x_r) + (y_r * y_r)));
            if (r > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = r;
            }
            // Calculate green
            g = (int)round(sqrt((x_g * x_g) + (y_g * y_g)));
            if (g > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = g;
            }
            // Calculate blue
            b = (int)round(sqrt((x_b * x_b) + (y_b * y_b)));
            if (b > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = b;
            }
        }
    }
    return;
}