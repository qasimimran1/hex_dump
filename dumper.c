
#include "dumper.h"

void dump_file(dumper_setting_t *dumper_opts)
{
    FILE *fp_input, *f_output;

    if (dumper_opts->input == FILE_IO)
    {
        fp_input = fopen(dumper_opts->fin_name, "rb");
        if (fp_input == NULL)
        {
            fprintf(stderr, "Error opening %s file \n", dumper_opts->fin_name);
            exit(1);
        }
    }
    else
    {
        fp_input = stdin;
    }

    if (dumper_opts->output == FILE_IO)
    {
        f_output = fopen(dumper_opts->fout_name, "wb");
        if (f_output == NULL)
        {
            fprintf(stderr, "Error opening %s file \n", dumper_opts->fout_name);
            exit(1);
        }
    }
    else
    {
        f_output = stdout;
    }

    uint32_t char_read = 0, address = 0, char_count = 0, fp_size = 0, total_read = 0;
    uint8_t _read[100];
    uint8_t *fBuff;

    if (dumper_opts->input == FILE_IO)
    {
        fseek(fp_input, 0, SEEK_END);
        fp_size = ftell(fp_input);
        rewind(fp_input);

        if (fp_size > 0)
        {
            fBuff = (uint8_t *)malloc(fp_size * sizeof(uint8_t));
        }
        else
        {
            fprintf(stderr, "%s File is Empty\n", dumper_opts->fin_name);
            fclose(fp_input);
            exit(1);
        }
        fread(fBuff, sizeof(uint8_t), fp_size, fp_input); // read the file into the buffer
        fclose(fp_input);
    }
    else
    {
        fBuff = (uint8_t *)malloc(MAX_READ * sizeof(uint8_t));
        fp_size = fread(fBuff, sizeof(uint8_t), MAX_READ, fp_input);
        //printf("fp_size: %d\n", fp_size);
    }

    for (uint32_t count = 0; count < fp_size; count++)
    {
        char_read = fBuff[count];
        _read[char_count++] = char_read;
        total_read++;

        if ((char_count % dumper_opts->col_size) == 0)
        {
            fprintf(f_output, "%08x | ", address);
            for (uint8_t i = 0; i < dumper_opts->col_size; i++)
            {
                fprintf(f_output, "%02x ", _read[i]);
            }
            fprintf(f_output, "| ");
            for (uint8_t i = 0; i < dumper_opts->col_size; i++)
            {
                if (_read[i] >= MIN && _read[i] <= MAX)
                {
                    fprintf(f_output, "%c", _read[i]);
                }
                else
                {
                    fprintf(f_output, ".");
                }
            }
            fprintf(f_output, " |\n");
            char_count = 0;
            address += dumper_opts->col_size;
        }
    } // end for loop

    if (char_count > 0) // for remaining characters
    {
        fprintf(f_output, "%08x | ", address);
        for (uint8_t i = 0; i < dumper_opts->col_size; i++)
        {
            if (i < char_count)
            {
                fprintf(f_output, "%02x ", _read[i]);
            }
            else
            {
                fprintf(f_output, "-- ");
            }
        }
        fprintf(f_output, "| ");
        for (uint8_t i = 0; i < dumper_opts->col_size; i++)
        {
            if (i < char_count)
            {
                if (_read[i] >= MIN && _read[i] <= MAX)
                {
                    fprintf(f_output, "%c", _read[i]);
                }
                else
                {
                    fprintf(f_output, ".");
                }
            }
            else
            {
                fprintf(f_output, "-");
            }
        }
        fprintf(f_output, " |\n");
    }
    free(fBuff);
}
