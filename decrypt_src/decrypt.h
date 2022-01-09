#ifndef __DECRYPT_H__
#define __DECRYPT_H__

#include <time.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

typedef struct
{
    char *file_data;
    long file_size;
    FILE *fd;
    char *file_path;

} file_struct;

file_struct *createFileStruct();
void destroyFileStruct(file_struct *);
int read_data(file_struct*, char *);
int decrypt_data(file_struct*, int);
int write_decrypted_data(file_struct*, char *);

#endif