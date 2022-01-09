#ifndef __ENCRYPT_H__
#define __ENCRYPT_H__

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
void destroyFileStruct(file_struct *file_str);
int read_data(file_struct*, char *);
int crypt_data(file_struct*, int);
int write_crypted_data(file_struct*, char *);

#endif