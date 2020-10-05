/*
 * Mini-ELF header verifier
 *
 * Name: Devdutt Santhosh
 */

#include "p1-check.h"

/**********************************************************************
 *                         REQUIRED FUNCTIONS
 *********************************************************************/

bool read_header (FILE *file, elf_hdr_t *hdr)
{
    /* Validate arguments */
    if (file == NULL || hdr == NULL) 
    {
        return false;
    }

    /* Try to read header, and check if correct header was read */
    if (fread(hdr, sizeof(elf_hdr_t), 1, file) != 1 || 
            hdr->magic != 0x00464c45) /* 0x00464c45 is "ELF\0" as number */
    {
        return false;
    }

    /* If we got here, the reading was successful */
    return true;
}

/**********************************************************************
 *                         OPTIONAL FUNCTIONS
 *********************************************************************/

void usage_p1 (char **argv)
{
    printf("Usage: %s <option(s)> mini-elf-file\n", argv[0]);
    printf(" Options are:\n");
    printf("  -h      Display usage\n");
    printf("  -H      Show the Mini-ELF header\n");
}

bool parse_command_line_p1 (int argc, char **argv, bool *header, char **filename)
{
    int opt;

    /* Check call arguments */
    if (argc <= 1 || argv == NULL || header == NULL || filename == NULL)
    {
        return false;
    }
    
    /* Set default "parsed" values */
    *header = false;
    *filename = NULL;

    /* Parse command line switches */
    while ((opt = getopt(argc, argv, "hH")) != -1)
    {
        switch (opt)
        {
            case 'h':
                /* Print usage and exit */
                usage_p1(argv);
                *header = false;
                *filename = NULL;
                return true;
                break;
            case 'H':
                /* Set header flag */
                *header = true;
                break;
            default:
                return false;
        }
    }

    /* Parse command line arguments */
    if (optind != argc - 1)
    {
        return false;
    }
    *filename = argv[optind];

    return true;
}

void dump_header (elf_hdr_t hdr)
{
    /* Print version */
    printf("Mini-ELF version %u\n", hdr.e_version);

    /* Print entry point */
    printf("Entry point %#x\n", hdr.e_entry);

    /* Print program headers info */
    printf("There are %u program headers, starting at offset %u (%#x)\n",
            hdr.e_num_phdr, hdr.e_phdr_start, hdr.e_phdr_start);

    /* Print symbol table info */
    if (hdr.e_symtab == 0)
    {
        printf("There is no symbol table present\n");
    }
    else
    {
        printf("There is a symbol table starting at offset %u (%#x)\n",
                hdr.e_symtab, hdr.e_symtab);
    }
    
    /* Print string table info */
    if (hdr.e_strtab == 0)
    {
        printf("There is no string table present\n");
    }
    else
    {
        printf("There is a string table starting at offset %u (%#x)\n",
                hdr.e_strtab, hdr.e_strtab);
    }
}

