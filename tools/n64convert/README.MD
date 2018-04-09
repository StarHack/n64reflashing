n64convert
----

This small utility allows you to convert among various N64 ROM formats.

![screenshot.png](https://i.imgur.com/3Guw3QU.png)

The tool supports the following formats:

- **.N64:** Little-endian format (makerom / No-Intro)
- **.V64:** Doctor V64's byte-swapped format
- **.Z64:** N64's native big-endian byte-order

Usage:
---

The program requires two parameters - the input file and the output file. The output file's format is determined by its extension, use .n64, .v64 or .z64.

**\*nix:**

`./n64convert input.v64 output.z64`

**Windows**

`n64convert.exe input.v64 output.z64`

Building:
---

**macOS:**

`llvm-gcc n64convert.c -o n64convert`

**Linux:**

`gcc n64convert.c -o n64convert`

**Windows:** (use MinGW or similar)

`gcc.exe n64convert.c -o n64convert`

