/*
 * Main driver
 *
 * Name: Devdutt Santhosh
 */

#include "p1-check.h"

int main (int argc, char **argv)
{
    int i;
    FILE *file;
    bool header;
    elf_hdr_t hdr;
    char *filename;

    /* Parse and check command-line arguments */
    if (!parse_command_line_p1(argc, argv, &header, &filename))
    {
        usage_p1(argv);
        return EXIT_FAILURE;
    }

    /* Check if we just printed help and should exit successfuly */
    if (filename == NULL)
    {
        return EXIT_SUCCESS;
    }

    /* Try to open the file and read it */
    if ((file = fopen(filename, "rb")) == NULL || !read_header(file, &hdr))
    {
        if (file != NULL)
        {
            fclose(file);
        }
        printf("Failed to read file\n");
        return EXIT_FAILURE;
    }
    fclose(file);

    /* Print the header bytes if needed */
    if (header)
    {
        for (i = 0; i < sizeof(elf_hdr_t); i++)
        {
            if (i != 0)
            {
                printf(" ");
                if (i % 8 == 0)
                {
                    printf(" ");
                }
            }
            printf("%02x", ((uint8_t *)(&hdr))[i]);
        }
        printf("\n");
    }

    /* Print the header info in readable format */
    dump_header(hdr);

    /* If we got here, the execution was successful */
    return EXIT_SUCCESS;
}

