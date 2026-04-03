# Radix

Radix is a CLI tool to convert numbers between binary, octal, decimal and hexadecimal bases.

## Usage

Radix can convert numbers passed as command line arguments (in which case they must appear as the last argument!) or via stdin (pipe or file redirect). If stdin is a redirected file, Radix will process each line as a separate number to be converted. If input is provided via stdin, Radix will ignore any non-flag command line input.

Radix accepts 3 optional flags:

```bash
radix -i bin -o dec 1010
# Converts Binary 1010 to Decimal 10. Outputs '10'.
radix -o hex 273
# Converts Decimal 273 to Hexadecimal 111. Outputs '111'.
radix -i hex -o bin FF
# Converts Hexadecimal FF to Binary 11111111. Outputs '11111111'.
```
Options -i and -o set the input and output base respectively. If either flag is not provided, that option defaults to DECIMAL.

Option -p will prepended the output with an appropriate prefix (see below in Base Autodetection), e.g.
```bash
radix -o hex -p 273
# Converts Decimal 273 to Hexadecimal 111. Outputs '0x111'.
```
Option -s will force the output to be signed. Note that negative numbers are always signed regardless of this option, but positive numbers will not be signed by default (as unsigned numbers are assumed to be positive).

Options can be set in any order (but the option argument must immediately follow its option).

NB: The current version of Radix only supports A-F in upper case for hexadecimal numbers.

### Valid Option Arguments

For binary, the accepted values are `bin, b, 2`

For octal, the accepted values are `oct, o, 8`

For decimal, the accepted values are `dec, d, 10`

For hexadecimal, the accepted values are `hex, h, 16`

All other values will result in validation failure.

### Base Autodetection

Non-Decimal numbers can be represented using a prefix:

- Binary -> 0b
- Octal  -> 0o
- Hex    -> 0x

(There is no prefix for decimal numbers as this is the assumed default base)

Radix will detect the presence of these prefixes, and use them to determine the input base. If a prefix is present, Radix will ignore the -i option for that input number and interpret it using the prefix.

## Exit Codes

Radix outputs a series of exit codes depending on the output of the operation. These are as follows:

0 - All Ok (Success).  
1 - Invalid option.  
2 - Provided option argument is invalid.  
3 - Input number has an invalid prefix.  
4 - Input number is invalid.  

## Installation

1. Clone this repository and build from source:
```bash
git clone <repo-url>
cd radix
cmake -S . -B build
cmake --build build
sudo cmake --install build   # optional
```

### Requirements / Dependencies

Radix requires the following in order to compile & run:

- C++23 compatible compiler
- CMake 3.16+

## Limitations
Radix currently supports up to (unsigned) 32bit integers. This means the maximum value that can be fed in is:  
  
Binary  -> 11111111111111111111111111111111  
Octal   -> 037777777777  
Decimal -> 4294967295  
Hex     -> FFFFFFFF  

Negative numbers are supported. The sign is stripped before conversion and re-applied afterwards, meaning all 32 bits are available for storing the number. Inputs larger than the above values will return the above values (UINT32_MAX in whatever base).

## Executing via TTY
If passing a negative input number from tty, you need to pass it after the '--'  separator otherwise the negative input number will be treated as an option, and return an error. There is no such requirement if passing the input number via pipe or file redirect.

## Contrivances and Quirks

The binary prefix '0b' is a valid hexadecimal number. Any binary number is also a valid hexadecimal number. This makes impossible to detect if a number such as 0b01 etc. is a hexidecimal number (equivalent to DEC:2817) or a binary number with a prefix (equivalent to DEC:1). In the current version, if the input starts with 0b, it will be interpreted as the prefix of a binary number and the rest of the input will be treated as such. So an input of 0bff will return a validation error (as it will try to validate 'ff' as a binary number). Any hexadecimal number starting '0b' should be prefixed with '0x' (the hexadecimal prefix) i.e. '0x0bff' instead of '0bff', to ensure proper function.
