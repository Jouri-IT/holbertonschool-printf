#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <unistd.h>

typedef struct specifier_s
{
	char spec;
	int (*handler)(va_list, char[], int *);
} specifier_t;

int _printf(const char *format, ...);

int buffer_char(char c, char buffer[], int *index);
int flush_buffer(char buffer[], int *index);

int print_char(va_list args, char buffer[], int *index);
int print_string(va_list args, char buffer[], int *index);
int print_percent(va_list args, char buffer[], int *index);
int print_int(va_list args, char buffer[], int *index);
int print_binary(va_list args, char buffer[], int *index);

#endif
