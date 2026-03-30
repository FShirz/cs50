#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // check single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open & read memory card
    FILE *card = fopen(argv[1], "r");

    if (card == NULL)
    {
        return 1;
    }

    // Create a buffer for a block of data
    unsigned char *buffer = malloc(512);
    // Create a string for filename
    char *filename = malloc(8);
    // Create a counter for images
    int image = 0;

    if (buffer == NULL)
    {
        return 1;
    }

    if (filename == NULL)
    {
        return 1;
    }
    // While there's still data left to read from the memory card
    while (fread(buffer, 1, 512, card) == 512)
    {
        // Check if it meets the criteria
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // Create format for filename
            sprintf(filename, "%03i.jpg", image);
            // wright the file
            FILE *imgf = fopen(filename, "w");
            if (imgf == NULL)
            {
                return 1;
            }
            fwrite(buffer, 1, 512, imgf);
            fclose(imgf);
            image++;
        }
        else if (image != 0)
        {
            // append the file
            FILE *imgf = fopen(filename, "a");
            if (imgf == NULL)
            {
                return 1;
            }
            fwrite(buffer, 1, 512, imgf);
            fclose(imgf);
        }
    }
    // Close the opened files and free the memmory
    fclose(card);
    free(buffer);
    free(filename);
}
