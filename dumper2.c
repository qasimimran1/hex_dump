
#include <stdbool.h>
#include "dumper.h"

FILE *fp_input, *f_output;
static uint32_t char_count = 0;

static void print_out(uint8_t *buf, uint32_t address, int16_t col_size, bool is_last)
{
    int16_t index_h = 0;
    int16_t index_a = 0;
    uint16_t separator = 0;
    char final_output[400] = {'1'};
    uint16_t p_count = 17 + (col_size * 4); // 17 is due to address and spaces and '|'

    index_h += snprintf(&final_output[index_h], ADDR_L, "%08x | ", address);
    separator = (index_h + (col_size * 3));
    index_a = separator + 3;

    for (int i = 0; i < col_size; i++)
    {
        if (is_last == false)
        {
            index_h += snprintf(&final_output[index_h], HEX_L, "%02x ", buf[i]);                     
            if (buf[i] >= MIN && buf[i] <= MAX)
            {
                index_a += snprintf(&final_output[index_a], ASC_L, "%c", buf[i]);
            }
            else
            {
                index_a += snprintf(&final_output[index_a], ASC_L, ".");
            }
        }
        else
        {
            if (i < char_count)
            {
                index_h += snprintf(&final_output[index_h], HEX_L, "%02x ", buf[i]);                
                if (buf[i] >= MIN && buf[i] <= MAX)
                {
                    index_a += snprintf(&final_output[index_a], ASC_L, "%c", buf[i]);
                }
                else
                {
                    index_a += snprintf(&final_output[index_a], ASC_L, ".");
                }
            }
            else
            {
                index_h += snprintf(&final_output[index_h], HEX_L, "-- ");                
                index_a += snprintf(&final_output[index_a], ASC_L, "-");
            }
        }
    }
    //snprintf(&final_output[separator], SPC_L, " | ");
    final_output[separator++] = ' '; 
    final_output[separator++] = '|';
    final_output[separator++] = ' ';
    index_a += snprintf(&final_output[index_a], HEX_L, " |\n");
    fwrite(final_output, sizeof(char), p_count, f_output);
}

void dump_file(dumper_setting_t *dumper_opts)
{
    uint32_t char_read = 0, address = 0, fp_size = 0, total_read = 0;
    uint8_t _read[100];
    uint8_t *fBuff;

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
    }

    for (uint32_t count = 0; count < fp_size; count++)
    {
        char_read = fBuff[count];
        _read[char_count++] = char_read;
        total_read++;

        if ((char_count % dumper_opts->col_size) == 0)
        {
            print_out(_read, address, dumper_opts->col_size, 0);
            char_count = 0;
            address += dumper_opts->col_size;
        }
    } // end for loop

    if (char_count > 0) // for remaining characters
    {
        print_out(_read, address, dumper_opts->col_size, 1);
    }
    free(fBuff);
}
