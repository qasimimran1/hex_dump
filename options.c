#include <getopt.h>
#include "options.h"
#include "dumper.h"

static struct option long_options[] = {
    {"help", no_argument, 0, 'h'},
    {"output", required_argument, 0, 'o'},
    {"columns", required_argument, 0, 'c'},
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
    uint8_t col_flag = 0, out_flag = 0, arg_count_flag = 0;

    for (size_t i = 0; i < argc; i++)
    {
        if (strcmp("--", argv[i]) == 0 && !arg_count_flag)
        {
            dumper_opts->fin_name = argv[i + 1];
            dumper_opts->input = FILE_IO;
            arg_count_flag = 1;
        }
        // if (save)
        // {
        //
        //     input_files[f_indx] = argv[i];
        //     //
        //     f_indx++;
        // }
    }

    while ((opt = getopt_long(argc, argv, "hc:o:",
                              long_options, &long_index)) != -1)
    {
        arg_count_flag = 2;
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
            if (!out_flag)
            {
                out_flag = 1;
                dumper_opts->fout_name = optarg;
                dumper_opts->output = FILE_IO;
            }
            else
            {
                fprintf(stderr, "Output file Opt repeated!!");
                exit(1);
            }

            break;
        }

        case 'c':
        {
            if (!col_flag)
            {
                col_flag = 1;
                dumper_opts->col_size = atoi(optarg);
                if (dumper_opts->col_size <= 0)
                {
                    fprintf(stderr, "Column Size SHOULD be greater than one!!");
                    exit(1);
                }
            }
            else
            {
                fprintf(stderr, "Col Opt repeated!!");
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
    if (!arg_count_flag && argc == 2)
    {
        dumper_opts->fin_name = argv[1];
        dumper_opts->input = FILE_IO;
    }
    if (!arg_count_flag && argc > 2)
    {

        fprintf(stderr, "Too many arguments without option");
        exit(1);
    }
    if (arg_count_flag == 2)
    {
        dumper_opts->fin_name = argv[argc - 1];
        dumper_opts->input = FILE_IO;
        // printf("file name: %s\n", dumper_opts->fin_name);
    }
}
