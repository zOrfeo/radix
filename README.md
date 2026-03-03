# Radix v0.1.0

Radix is a CLI tool to convert numbers between binary, octal, decimal and hexadecimal bases.

## Usage

Radix can convert numbers passed as command line arguments (in which case they must appear as the last argument!) or via stdin. If stdin is a redirected file, Radix will process each line as a separate number to be converted. If input is provided via stdin, Radix will ignore any non-flag command line input.

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

Options can be set in any order (but the option argument must immediately follow its option).

NB: The current version of Radix only supports hexadecimal digits A-F in upper case.

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

- C++17 compatible compiler
- CMake 3.16+

## Limits
Radix currently supports up to (unsigned) 32bit integers. This means the maximum value that can be fed in is:  
  
Binary  -> 11111111111111111111111111111111  
Octal   -> 037777777777  
Decimal -> 4294967295  
Hex     -> FFFFFFFF  

Negative numbers will currently fail validation. Inputs larger than the above will return the above.

### Case sensitivity in inputs

All inputs are case sensitive. For the input number (to be converted) this is because the prefix '0b', used to indicate the number is binary, cannot be distinguished from the lower case hexadecimal number '0b' (DEC:11).
