#include "main.h"

#define BUF_SIZE 1024

/**
 * flush_buffer - writes buffer to stdout
 */
int flush_buffer(char buffer[], int *index)
{
	int count;

	count = 0;
	if (*index > 0)
	{
		write(1, buffer, *index);
		count = *index;
		*index = 0;
	}
	return (count);
}

/**
 * buffer_char - adds char to buffer
 */
int buffer_char(char c, char buffer[], int *index)
{
	if (*index == BUF_SIZE)
		flush_buffer(buffer, index);

	buffer[*index] = c;
	(*index)++;

	return (1);
}

/**
 * print_char - handles %c
 */
int print_char(va_list args, char buffer[], int *index)
{
	char c;

	c = (char)va_arg(args, int);
	return (buffer_char(c, buffer, index));
}

/**
 * print_string - handles %s
 */
int print_string(va_list args, char buffer[], int *index)
{
	char *str;
	int count;

	str = va_arg(args, char *);
	if (!str)
		str = "(null)";
	count = 0;

	while (*str)
		count += buffer_char(*str++, buffer, index);

	return (count);
}

/**
 * print_percent - handles %%
 */
int print_percent(va_list args, char buffer[], int *index)
{
	(void)args;
	return (buffer_char('%', buffer, index));
}

/**
 * print_int - handles %d %i
 */
int print_int(va_list args, char buffer[], int *index)
{
	int n;
	unsigned int u;
	int count;
	unsigned int divisor;

	n = va_arg(args, int);
	count = 0;

	if (n < 0)
	{
		count += buffer_char('-', buffer, index);
		u = (unsigned int)(-(n + 1)) + 1;
	}
	else
		u = (unsigned int)n;

	divisor = 1;
	while (u / divisor >= 10)
		divisor *= 10;

	while (divisor >= 1)
	{
		count += buffer_char('0' + (u / divisor % 10), buffer, index);
		divisor /= 10;
	}
	return (count);
}
