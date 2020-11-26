# hex_dump
The program reads in from the input some data and then shows the bytes in hexadecimal numerals as well as plain ASCII.
Each line also shows the offset of the address that these bytes are at.

## Command line arguments

There are a few arguments as can be seen from the help option:

```
Usage: ./dumper [-c cols] [-o output] [--] [input]
Options:
  -c, --columns    Set output max columns (min 1, default 16)
  -o, --output     Set output file (stdout default)
  -h, --help       Show this help
  --               Stop interpreting options (filename is "--help" etc.)
  inputs           Read all the files (stdin default)
