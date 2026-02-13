# Radix v0.1.0

Radix is a CLI tool to convert numbers between binary, octal, decimal and hexadecimal bases.

## Usage

```bash
./radix -i dec -o hex 111
```
Radix accepts 2 optional flags, -i and -o, to set the input and output base. If either flag is not provided, that option defaults to DECIMAL.

The number to be converted must appear as the last argument.

NB: The current version of Radix only supports hexadecimal digits A-F in upper case.

### Valid Option Arguments

For binary, the accepted values are `bin, b, 2`

For octal, the accepted values are `oct, o, 8`

For decimal, the accepted values are `dec, d, 10`

FOr hexadecimal, the accepted values are `hex, h, 16`

All other values will result in validation failure.

### Base Autodetection

Non-Decimal numbers can be represented using a prefix:

Binary -> 0b
Octal  -> 0o
Hex    -> 0x

(There is no prefix for decimal numbers as this is the assumed default base)

Radix will detect the presence of these prefixes, and use them to determine the input base if the input flag is not set. If the input flag is set and a contradictory prefix present, Radix will ignore the prefix and interpret the input number as one with the base set by the -i flag.

## Installation

1. Clone this repository and build from source.
