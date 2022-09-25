//
// Created by ralim on 25/09/22.
//

#include <malloc.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

ssize_t get_file_contents(const char* file_path_on_disk, uint8_t ** file_contents);

// Parse a .dfu file and extract its payload and metadata
int dfu_file_parse(const char* file_path_on_disk){
    uint8_t* dfu_file_contents =NULL;
    ssize_t  file_size = get_file_contents(file_path_on_disk,&dfu_file_contents);
    
    return -1;
}

//Returns file size _or_ negative on error
ssize_t get_file_contents(const char* file_path_on_disk, uint8_t ** file_contents){
    size_t read_count;
    size_t file_size=0;
    size_t read_total = 0;
    file_contents=NULL;
    FILE* f;
    f = fopen(file_path_on_disk, "rb");
    if (f < 0)
    {
        fprintf(stderr, "Could not open file %s for reading", file_path_on_disk);
        return -1;
    }


    file_size = fseek(f, 0, SEEK_END);

    fseek(f,0,SEEK_SET);
    *file_contents = calloc(file_size,sizeof(uint8_t));



    while (read_total < file_size) {
        size_t to_read = file_size - read_total;
        /* read() limit on Linux, slightly below MAX_INT on Windows */
        if (to_read > 0x7ffff000)
            to_read = 0x7ffff000;
        read_count = fread((*file_contents) + read_total, to_read,1,f);
        if (read_count == 0)
            break;
        //If error and not end of file, break
        if (read_count == -1 && !feof(f))
            break;
        read_total += read_count;
    }
    if (read_total != file_size) {
        fprintf(stderr, "Could only read %lld of %lld bytes from %s",
            (long long) read_total, (long long) file_size, file_path_on_disk);
        return -1;
    }
    fclose(f);
    return (ssize_t)file_size;

}