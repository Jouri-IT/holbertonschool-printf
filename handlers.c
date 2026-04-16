#include "main.h"

#define BUF_SIZE 1024

int flush_buffer(char buffer[], int *index)
{
	int count = 0;

	if (*index > 0)
	{
		write(1, buffer, *index);
		count = *index;
		*index = 0;
	}
	return (count);
}

int buffer_char(char c, char buffer[], int *index)
{
	if (*index == BUF_SIZE)
		flush_buffer(buffer, index);

	buffer[*index] = c;
	(*index)++;

	return (1);
}

int print_char(va_list args, char buffer[], int *index, char flag)
{
	char c;

	(void)flag;
	c = (char)va_arg(args, int);
	return (buffer_char(c, buffer, index));
}

int print_string(va_list args, char buffer[], int *index, char flag)
{
	char *str;
	int count = 0;

	(void)flag;
	str = va_arg(args, char *);
	if (!str)
		str = "(null)";

	while (*str)
		count += buffer_char(*str++, buffer, index);

	return (count);
}

int print_percent(va_list args, char buffer[], int *index, char flag)
{
	(void)args;
	(void)flag;
	return (buffer_char('%', buffer, index));
}

int print_int(va_list args, char buffer[], int *index, char flag)
{
	int n;
	unsigned int u;
	int count = 0;
	unsigned int divisor;
	char sign = 0;

	n = va_arg(args, int);

	if (n < 0)
		sign = '-';
	else if (flag == '+')
		sign = '+';
	else if (flag == ' ')
		sign = ' ';

	if (sign)
		count += buffer_char(sign, buffer, index);

	if (n < 0)
		u = (unsigned int)(-(n + 1)) + 1;
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
