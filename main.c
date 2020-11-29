#include <string.h>
#include "options.h"
#include "dumper.h"
#define NO_OF_FILES 10
#define FILE_NAME_LEN 20

int main(int argc, char **argv)
{

    // Set default settings
    dumper_setting_t dumper_opts;
    dumper_opts.fin_name = NULL;
    dumper_opts.fout_name = NULL;
    dumper_opts.input = STD_IO;
    dumper_opts.output = STD_IO;
    dumper_opts.col_size = 16;

    process_options(argc, argv, &dumper_opts);

    if (dumper_opts.fout_name != NULL)
    {
        dumper_opts.output = FILE_IO;
    }
    dump_file(&dumper_opts);

    return 0;
}
