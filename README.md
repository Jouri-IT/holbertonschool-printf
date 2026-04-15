# _printf

This project is a custom implementation of the standard C function `printf`. It prints formatted output to the standard output (stdout).

## Prototype

```c
int _printf(const char *format, ...);
```


Description

The _printf function produces output according to a format string. It handles basic format specifiers and writes the result to stdout.

Compilation

gcc -Wall -Werror -Wextra -pedantic -std=gnu89 -Wno-format *.c

Supported specifiers

%c : prints a single character
%s : prints a string
%% : prints a percent sign

Example

_printf("Hello %s, char: %c, percent: 100%%\n", "world", 'A');

Return value

Returns the number of characters printed (excluding the null byte).
Returns -1 if format is NULL.

## Authors

- Tala Alhudhaybi  
- Jouri Jouri