#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //ensuring only one input in void main
    if (argc != 2)
    {
        printf("Type only one word");
        return 1;
    }
    //saving file into a string name c
    char *c = argv[1];

    //input file open with FILE function
    FILE *input = fopen(c, "r");

    if (input == NULL)
    {
        printf("Error : File cannot be read");
        return 1;
    }

    // generate variable for 512
    const int BLOCK_SIZE = 512;

    //declare a function where to store a data from fread.
    BYTE byte[BLOCK_SIZE];

    int i = 0;

    char *output = malloc(8 * sizeof(char));
    if (output == NULL)
    {
        //printf("memory allocation null");
        return 1;
    }

    FILE *img = NULL;

    //read the file like told to
    while (fread(byte, sizeof(BYTE), BLOCK_SIZE, input) == BLOCK_SIZE)
    {
        //checking if the file is jpf format or not

        //checking if this is the first time jpg file is read
        if (byte[0] == 0xff && byte[1] == 0xd8 && byte[2] == 0xff && ((byte[3] & 0xf0) == 0xe0))
        {
            if (i > 0)
            {
                fclose(img);
            }

            //saving unique file name to a string starting from 0
            sprintf(output, "%03i.jpg", i);

            //now forming an output jpg file with that name and opening the file
            img = fopen(output, "w");

            if (img == NULL)
            {
                return 1;
            }
            i ++;
        }
        if (img != NULL)
        {
            //img = fopen(output, "w");
            //fprintf(img, "%s",byte);
            fwrite(byte, sizeof(BYTE), 512, img);
        }
    }
    free(output);
    fclose(img);
    fclose(input);
}