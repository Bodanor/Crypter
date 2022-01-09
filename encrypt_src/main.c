#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

#include "encrypt.h"

int main(int argc, char *argv[])
{

    const char *opstring = ":s:i:o:h";
    int val;
    int status;

    int seed = 0, input_flag = 0, output_flag = 0;
    char *input_file = NULL;
    char *output_file = NULL;

    while ((val = getopt(argc, argv, opstring)) != EOF){
        switch(val)
        {
            case 'h':
                printf("Usage :\n\n./encrypt <inputfile>\n\nOPTIONS :\n\n-s\tSet the base seed for the randomness\n-i\tInput file to be encrypted\n-o\tOutput file to write to \n");
                return 0;
                break;
            case 'i':
                input_file = optarg;
                input_flag = 1;
                break;
            case 'o':
                output_file = optarg;
                output_flag = 1;
                break;
            case 's':
                int i, digit_check = 0;
                for (i = 0; i < strlen(optarg); i++)
                {
                    if (isdigit(*(optarg + i)) == 0)
                        digit_check = -1;
                }
                if (digit_check == -1)
                    printf("Bad argument for seed (not a digit ?). Defaulting to 0\n");
    
                seed = atoi(optarg);
                break;
            case '?':
                printf("Unknown option: %c\n", optopt);
                break;
            
            case ':':
                printf("Missing arg: %c\n", optopt);
                break;
        }
    }

    if (argc <= 1)
    {
        printf("[ERROR] Input file missing !\n");
        printf("Usage :\n\n./encrypt <inputfile>\n\nOPTIONS :\n\n-s\tSet the base seed for the randomness\n-i\tInput file to be encrypted\n-o\tOutput file to write to \n");
        return 0;
    }
    if (input_flag == 0 && output_flag == 0)
    {
        input_file = argv[optind];
        output_file = input_file;
    }
    if (input_flag == 0 && output_flag == 1)
    {
        input_file = argv[optind];
    }
    else if (input_flag == 1 && output_flag == 0)
    {
        output_file = input_file;
    }
    file_struct *file_str = createFileStruct();
    status = read_data(file_str, input_file);
    if (status == -1)
    {
        printf("Couldn't open and read file !\n");
        destroyFileStruct(file_str);
        return 0;
        // Free struct !
    }
    else if (status == -2)
    {
        printf("Memory Error !\n");
        destroyFileStruct(file_str);
        return 0;
        // Free Struct !
    }

    crypt_data(file_str, seed);

    status = write_crypted_data(file_str, output_file);
    if (status == -1)
    {
        printf("Couldn't write to file !\n");
        destroyFileStruct(file_str);
        return 0;
        // Free struct !
    }

    printf("File Encrypted successfully !\n");

    destroyFileStruct(file_str);
}