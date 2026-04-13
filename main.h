#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <unistd.h>

/**
 * struct specifier_s - Pairs a format specifier with its handler
 * @spec: The format character
 * @handler: Pointer to the handler function
 */
typedef struct specifier_s
{
	char spec;
	int (*handler)(va_list);
} specifier_t;

int _printf(const char *format, ...);
int print_char(va_list args);
int print_string(va_list args);
int print_percent(va_list args);
int print_int(va_list args);
int write_char(char c);

#endif /* MAIN_H */
