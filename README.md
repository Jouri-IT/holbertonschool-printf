# _printf

A custom implementation of the C standard library printf function.

## Compilation

gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c

## Supported specifiers

| Specifier | Output |
|-----------|--------|
| %c | Single character |
| %s | String |
| %% | Literal percent sign |

## Example

_printf("Hello %s, char: %c, percent: 100%%\n", "world", 'A');
// Output: Hello world, char: A, percent: 100%

## Authors

Your Name
