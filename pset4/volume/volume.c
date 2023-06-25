// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    uint8_t buffer[HEADER_SIZE];
    int16_t suffer;

    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    fread (buffer, HEADER_SIZE, sizeof(uint8_t), input);
    fwrite (buffer, HEADER_SIZE, sizeof(uint8_t), output);


    // TODO: Read samples from input file and write updated data to output file
    while (fread (&suffer, sizeof(int16_t), 1, input))
    {
        //fread (&suffer, 2, i + 1, input);
        suffer = suffer * factor;
        fwrite (&suffer, sizeof(int16_t), 1, output);

    }

    // Close files
    fclose(input);
    fclose(output);
}
