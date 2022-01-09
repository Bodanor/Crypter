#include "decrypt.h"

file_struct *createFileStruct()
{
    file_struct *file_str = malloc(sizeof(file_struct));
    if (file_str == NULL)
        return NULL;
    else
        return file_str;
}

int read_data(file_struct* file_str, char *file_path)
{
    assert (file_str != NULL);
    assert(file_path != NULL);

    file_str->fd = fopen(file_path, "rb");
    if (file_str->fd == NULL)
        return -1;
    file_str->file_path = file_path;
    fseek(file_str->fd, 0, SEEK_END);
    file_str->file_size = ftell(file_str->fd);
    fseek(file_str->fd, 0, SEEK_SET);

    file_str->file_data = malloc(file_str->file_size + 1);
    if (file_str->file_data == NULL)
        return -2;
    fread(file_str->file_data, file_str->file_size, 1, file_str->fd);
    fclose(file_str->fd);

    return 0;
}

int decrypt_data(file_struct* file_str, int seek)
{
    assert(file_str != NULL);

    long i;
    srand(seek);
    char *file_data_ptr = file_str->file_data;

    for (i = 0; i < file_str->file_size; i++)
    {
        *file_data_ptr++ -= rand();
    }

    return 0;
}

int write_decrypted_data(file_struct* file_str, char *file_path)
{
    assert(file_str != NULL);

    file_str->fd = fopen(file_path, "wb");
    if (file_str->fd == NULL)
        return -1;

    fwrite(file_str->file_data, file_str->file_size, 1, file_str->fd);

    return 0;

}

void destroyFileStruct(file_struct *file_str)
{
    assert(file_str != NULL);
    if (file_str->file_data != NULL)

        free(file_str->file_data);

    if (file_str->fd != NULL)
        fclose(file_str->fd);
    
    free(file_str);
}