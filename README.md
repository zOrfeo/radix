# Radix

**Radix** is a lightweight CLI tool for converting numbers between binary, octal, decimal, and hexadecimal bases.

It is designed to be simple, predictable, and easy to integrate into shell workflows.

---

## Documentation

- [Manual](docs/MANUAL.md)

--

## Features

- Convert between common bases: binary, octal, decimal, hexadecimal
- Accepts input via arguments, pipes, or file redirection
- Base autodetection using standard prefixes (`0b`, `0o`, `0x`)
- Optional prefix formatting for output
- Supports signed and unsigned values
- Consistent exit codes for scripting

---

## Quick Start

```bash
radix -i bin -o dec 1010
# → 10

radix -o hex 273
# → 111

echo 42 | radix -o bin
# → 101010
```

---

## Installation

### Arch Linux
[Install via AUR](https://aur.archlinux.org/packages/radix/)

via yay:
```bash
yay -S radix
```

### Debian / Ubuntu
Download the latest `.deb` from the [releases page.](https://github.com/zOrfeo/radix/releases/latest)

---

## Usage

Radix accepts input either:
- as a positional argument, or
- via standard input (stdin)

Examples:
```bash
radix -o bin 42
radix -i hex -o dec FF
radix -o hex < numbers.txt
```

For full usage details, options, and edge cases, see the manual:

```bash
man radix
```

---

## Notes

- Decimal is the default input and output base
- Prefixes (`0b`, `0o`, `0x`) override the specified input base
- Hexadecimal input currently requires uppercase letters (`A–F`)
- When passing negative numbers via CLI, use `--`:
  ```bash
  radix -o bin -- -42
  ```

---

## Limitations

- Supports up to 32-bit unsigned integers
- Larger values are clamped to the maximum (`UINT32_MAX`)

---

## Building from Source

### Requirements
- C++23 compatible compiler
- CMake 3.16+

### Build
```bash
git clone https://github.com/zOrfeo/radix.git
cd radix
cmake -B build
cmake --build build
```

---

## Contributing
Please report any bugs using the Github Issue Tracker along with any suggestions for new features or capabilities.

I am happy to accept pull requests if you want to fix/apply them yourself.
