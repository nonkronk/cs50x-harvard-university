#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// FAT block size
const int block_size = 512;

int main(int argc, char *argv[])
{
    // Check for invalid usage
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Open file
    FILE *inptr = fopen(argv[1], "r");
    if (!inptr)
    {
        return 1;
    }

    // Get 512 bytes block of memory
    unsigned char buffer[block_size];

    // Store how many jpeg found
    int count_jpg = 0;

    // Initialize null pointer
    FILE *outptr = NULL;

    // Define max array of filename
    char filename[sizeof "000.jpg"];

    // While we can read block from image
    while (fread(buffer, block_size, 1, inptr) == 1)
    {
        // Check first three bytes
        if ((buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) || outptr == NULL)
        {
            if (outptr != NULL)
            {
                fclose(outptr);
            }

            // Open new file
            outptr = fopen(filename, "w");
            sprintf(filename, "%03i.jpg", count_jpg);
            count_jpg++;
        }
        // Write each block
        fwrite(&buffer, block_size, 1, outptr);
    }

    // Close if still open
    if (outptr != NULL)
    {
        fclose(outptr);
    }
    fclose(inptr);
    return 0;
}
