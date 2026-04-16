#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <unistd.h>

typedef struct specifier_s
{
	char spec;
	int (*handler)(va_list);
} specifier_t;

int _printf(const char *format, ...);

int write_char(char c);

int print_char(va_list args);
int print_string(va_list args);
int print_percent(va_list args);
int print_int(va_list args);

int print_binary(va_list args);

int print_unsigned(va_list args);
int print_octal(va_list args);
int print_hex_lower(va_list args);
int print_hex_upper(va_list args);
int print_base_unsigned(unsigned int n, char *base);

#endif
