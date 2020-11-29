#include <string.h>
#include "options.h"
#include "dumper.h"
#define NO_OF_FILES 10
#define FILE_NAME_LEN 20

// char** create_file_matrix(int nrows, int ncols) {
// 	// first of all allocate space for the rows
// 	// each entry is the size of an char pointer
// 	char **m = malloc(nrows*sizeof(char*));

// 	// for each row, allocate space for the columns
// 	// each entry is the size of an char
// 	for(int i=0; i<nrows; i++) {
// 		m[i] = malloc(ncols*sizeof(char));
// 	}

// 	return m;
// }

int main(int argc, char **argv)
{

    // Set default settings
    // char **input_files    = create_file_matrix(NO_OF_FILES, FILE_NAME_LEN);
    dumper_setting_t dumper_opts;
    dumper_opts.fin_name = NULL;
    dumper_opts.fout_name = NULL;
    dumper_opts.input = STD_IO;
    dumper_opts.output = STD_IO;
    dumper_opts.col_size = 16;

    process_options(argc, argv, &dumper_opts);

    // if (dumper_opts.fin_name != NULL)
    // {

    //     for (size_t i = 0; i < sizeof(dumper_opts.fin_name); i++)
    //     {
    //         printf("fin_name %s: \n",  dumper_opts.fin_name[i]);
    //     }

    // }
    if (dumper_opts.fout_name != NULL)
    {
        dumper_opts.output = FILE_IO;
        //printf("fout_name %s: \n", dumper_opts.fout_name);
    }
    dump_file(&dumper_opts);

    
    // for (size_t i = 0; i < f_indx; i++)
    // {
    //   dumper_opts.fin_name =  input_files[i];
    //   printf("inputfile name: %s\n", dumper_opts.fin_name);
    //   dump_file(&dumper_opts);
    // }

    //   dump_file(&dumper_opts);

    //  for(int i=0; i<NO_OF_FILES; i++) {
    // 	free(input_files[i]);
    // }
    //	free(input_files);

    return 0;
}
