## RADIX(1)

## NAME
    radix — convert numbers between binary, octal, decimal, and hexadecimal

## SYNOPSIS
    radix [OPTIONS] [NUMBER]

## DESCRIPTION
    radix converts integers between common numeral systems: binary, octal,
    decimal, and hexadecimal.

    Input may be provided as a command-line argument or via standard input
    (stdin). When reading from stdin, positional arguments are ignored.
    When input is redirected from a file, each line is processed as a
    separate value.

## OPTIONS
    -i BASE
        Specify the input base.

    -o BASE
        Specify the output base.

        The default base is decimal for both input and output.

    -p
        Prepend the output with a base prefix:
            binary:      0b
            octal:       0o
            hexadecimal: 0x

    -s
        Force signed output. Positive values are unsigned by default.
        Negative values are always signed.

## BASES
    The following values are accepted for BASE:

        binary:      bin, b, 2
        octal:       oct, o, 8
        decimal:     dec, d, 10
        hexadecimal: hex, h, 16

    Invalid values result in an error.

## BASE AUTODETECTION
    radix supports base autodetection using prefixes:

        0b    binary
        0o    octal
        0x    hexadecimal

    If a prefix is present, it overrides the -i option.

    Decimal input has no prefix and is assumed by default.

## INPUT
    A NUMBER may be provided as a positional argument or via stdin.

    Examples:

        radix -i bin -o dec 1010
        radix -o hex 273
        echo 42 | radix -o bin
        radix -o hex < file.txt

## EXIT STATUS
    0    Success
    1    Invalid option
    2    Invalid option argument
    3    Invalid prefix
    4    Invalid input

## LIMITATIONS
    radix supports up to 64-bit (unsigned) integers.

    Maximum values:

        binary:      1111111111111111111111111111111111111111111111111111111111111111
        octal:       01777777777777777777777
        decimal:     18446744073709551615
        hexadecimal: FFFFFFFFFFFFFFFF

    Values exceeding these limits are clamped to the maximum value.

    Negative values are supported. The sign is removed before conversion
    and reapplied to the result.

## NOTES
    When passing a negative value as a command-line argument, use '--' to
    terminate option parsing:

        radix -o bin -- -42

    This is not required when using stdin.

## BUGS
    Values beginning with "0b" are always interpreted as binary. This may
    conflict with valid hexadecimal representations. Prefix hexadecimal
    values explicitly with "0x" to avoid ambiguity.
