#ifndef DUMPER_H
#define DUMPER_H

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>

#define MIN 0x20
#define MAX 0x7e
#define COL 16
#define MAX_READ 1024 * 1024

typedef enum
{
    STD_IO,
    FILE_IO,
} io_type_t;

typedef struct
{
    io_type_t input;
    io_type_t output;
    char *fin_name;
    char *fout_name;
    int16_t col_size;
} dumper_setting_t;

void dump_file(dumper_setting_t *dumper_opts);

#endif