#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <unistd.h>

typedef struct specifier_s
{
	char spec;
	int (*handler)(va_list, char[], int *, char, char, int, int);
} specifier_t;

int _printf(const char *format, ...);

int buffer_char(char c, char buffer[], int *index);
int flush_buffer(char buffer[], int *index);
int print_padding(int width, int len, char buffer[], int *index);

int print_char(va_list, char[], int *, char, char, int, int);
int print_string(va_list, char[], int *, char, char, int, int);
int print_percent(va_list, char[], int *, char, char, int, int);
int print_int(va_list, char[], int *, char, char, int, int);
int print_unsigned(va_list, char[], int *, char, char, int, int);
int print_octal(va_list, char[], int *, char, char, int, int);
int print_hex_lower(va_list, char[], int *, char, char, int, int);
int print_hex_upper(va_list, char[], int *, char, char, int, int);

#endif
int print_reverse(va_list args, char buffer[], int *index, char flag, char length, int width, int precision);
int print_rot13(va_list args, char buffer[], int *index, char flag, char length, int width, int precision);
