#include "main.h"

#define BUF_SIZE 1024

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

int buffer_char(char c, char buffer[], int *index)
{
	if (*index == BUF_SIZE)
		flush_buffer(buffer, index);

	buffer[*index] = c;
	(*index)++;

	return (1);
}

int print_char(va_list args, char buffer[], int *index, char flag, char length)
{
	char c;

	(void)flag;
	(void)length;
	c = (char)va_arg(args, int);
	return (buffer_char(c, buffer, index));
}

int print_string(va_list args, char buffer[], int *index, char flag, char length)
{
	char *str;
	int count;

	(void)flag;
	(void)length;
	str = va_arg(args, char *);
	if (!str)
		str = "(null)";
	count = 0;

	while (*str)
		count += buffer_char(*str++, buffer, index);

	return (count);
}

int print_percent(va_list args, char buffer[], int *index, char flag, char length)
{
	(void)args;
	(void)flag;
	(void)length;
	return (buffer_char('%', buffer, index));
}

int print_int(va_list args, char buffer[], int *index, char flag, char length)
{
	long int n;
	unsigned long int u;
	int count;
	unsigned long int divisor;
	char sign;

	if (length == 'l')
		n = va_arg(args, long int);
	else if (length == 'h')
		n = (short)va_arg(args, int);
	else
		n = va_arg(args, int);

	count = 0;
	sign = 0;

	if (n < 0)
		sign = '-';
	else if (flag == '+')
		sign = '+';
	else if (flag == ' ')
		sign = ' ';

	if (sign)
		count += buffer_char(sign, buffer, index);

	if (n < 0)
		u = (unsigned long int)(-n);
	else
		u = (unsigned long int)n;

	divisor = 1;
	while (u / divisor >= 10)
		divisor *= 10;

	while (divisor)
	{
		count += buffer_char('0' + (u / divisor % 10), buffer, index);
		divisor /= 10;
	}

	return (count);
}
