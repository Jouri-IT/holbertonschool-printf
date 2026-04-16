#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <unistd.h>

typedef struct specifier_s
{
	char spec;
	int (*handler)(va_list, char[], int *, char);
} specifier_t;

int _printf(const char *format, ...);

int buffer_char(char c, char buffer[], int *index);
int flush_buffer(char buffer[], int *index);

int print_char(va_list args, char buffer[], int *index, char flag);
int print_string(va_list args, char buffer[], int *index, char flag);
int print_percent(va_list args, char buffer[], int *index, char flag);
int print_int(va_list args, char buffer[], int *index, char flag);
int print_binary(va_list args, char buffer[], int *index, char flag);
int print_unsigned(va_list args, char buffer[], int *index, char flag);
int print_octal(va_list args, char buffer[], int *index, char flag);
int print_hex_lower(va_list args, char buffer[], int *index, char flag);
int print_hex_upper(va_list args, char buffer[], int *index, char flag);
int print_S(va_list args, char buffer[], int *index, char flag);
int print_pointer(va_list args, char buffer[], int *index, char flag);

#endif
