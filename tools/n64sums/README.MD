n64sums
----

This utility allows you to recompute both CRC sums of a ROM file. Valid checksums are required, otherwise the ROM won't boot.

The code is based on the work of Andreas Sterbenz (written/RE'd  (C) 1997 Andreas Sterbenz <stan@sbox.tu-graz.ac.at>).

Usage:
---

The program takes one parameter which is the ROM file to be tested.

**\*nix:**

`./n64sums input.z64`

**Windows**

`n64sums.exe input.z64`

Building:
---

**macOS:**

`llvm-gcc n64sums.c -o n64sums`

**Linux:**

`gcc n64convert.c -o n64convert`

**Windows:** (use MinGW or similar)

`gcc.exe n64convert.c -o n64convert.exe`

