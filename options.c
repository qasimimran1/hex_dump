#include <getopt.h>
#include "options.h"
#include "dumper.h"

static struct option long_options[] = {
    {"help", no_argument, 0, 'h'},
    {"output", required_argument, 0, 'o'},
    {"column", required_argument, 0, 'c'},
    {0, 0, 0, 0}};

void print_usage(void)
{
    printf("Usage: ./dumper [-c cols] [-o output] [--] [input]\n"
           "Options:\n"
           "\t-c, --columns    Set output max columns (min 1, default 16)\n"
           "\t-o, --output     Set output file (stdout default)\n"
           "\t-h, --help       Show this help\n"
           "\t--               Stop interpreting options\n"
           "\tinputs           Read all the files (stdin default)\n"

    );
}

void process_options(int argc, char *const *argv, dumper_setting_t *dumper_opts)
{
    int opt = 0;
    int long_index = 0;
    

    while ((opt = getopt_long(argc, argv, "hc:o:",
                              long_options, &long_index)) != -1)
    {
        switch (opt)
        {
        case 'h':
        {
            print_usage();
            exit(1);
        }
        break;
        case 'o':
        {
            dumper_opts->fout_name = optarg;
            dumper_opts->output = FILE_IO;
            break;
        }

        case 'c':
        {
            dumper_opts->col_size = atoi(optarg);
            if (dumper_opts->col_size <= 0)
            {
                fprintf(stderr, "Column Size SHOULD be greater than zero!!");
                exit(1);
            }
            break;
        }
        default:
        {
            print_usage();
            exit(EXIT_FAILURE);
        }
        }
    }
}
