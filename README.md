C CHR-UM6 POSIX driver
----------------------

A plain C CHR-UM6 packet parser/composer and driver.
This piece of software is work in progress - everyone is invited
to contribute to it, including:
* bugfixes
* portabiliy (OS / CPU architecture)
* generic usage concept / API definition

The current architecture idea is to separate between
* register payload bit definitions (folder: "regs"),
* wire format (folder: "wire\_format"), including
   * common bit and size definitions ("um6\_packet\_bits.h")
   * parser ("um6\_parser.[ch]")
   * composer ("um6\_composer.[ch]"), and 
* tests (folder: "tests")

