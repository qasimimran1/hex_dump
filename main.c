#include <string.h>
#include "options.h"
#include "dumper.h"
#define NO_OF_FILES 10
#define FILE_NAME_LEN 20

char **create_file_matrix(int nrows, int ncols)
{
    // first of all allocate space for the rows
    // each entry is the size of an char pointer
    char **m = malloc(nrows * sizeof(char *));

    // for each row, allocate space for the columns
    // each entry is the size of an char
    for (int i = 0; i < nrows; i++)
    {
        m[i] = malloc(ncols * sizeof(char));
    }

    return m;
}

int main(int argc, char **argv)
{

    // Set default settings

    dumper_setting_t dumper_opts;
    dumper_opts.fin_name = NULL;
    dumper_opts.fout_name = NULL;
    dumper_opts.input = STD_IO;
    dumper_opts.output = STD_IO;
    dumper_opts.col_size = 16;

    uint8_t save = 0, f_indx = 0, start_indx = 0;

    for (size_t i = 0; i < argc; i++)
    {
        if (strcmp("--", argv[i]) == 0)
        {
            save = 1;
            i++;
            start_indx = i;
        }
        if (save)
        {
            f_indx++;
        }
    }

    char **input_files = create_file_matrix(f_indx, FILE_NAME_LEN);
    for (size_t i = 0; i < f_indx; i++)
    {
        input_files[i] = argv[start_indx + i];
    }

    process_options(argc, argv, &dumper_opts);

    if (dumper_opts.fout_name != NULL)
    {
        dumper_opts.output = FILE_IO;
        printf("fout_name %s: \n", dumper_opts.fout_name);
    }
    if (f_indx > 0)
    {
        dumper_opts.input = FILE_IO; 
        for (size_t i = 0; i < f_indx; i++)
        {
            dumper_opts.fin_name = input_files[i];
            printf("inputfile name: %s\n", dumper_opts.fin_name);
            dump_file(&dumper_opts);
        }
    }
    else
    {
        dump_file(&dumper_opts);
    }

    //   dump_file(&dumper_opts);

    //  for(int i=0; i<NO_OF_FILES; i++) {
    // 	free(input_files[i]);
    // }
    free(input_files);

    return 0;
}
