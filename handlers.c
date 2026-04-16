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

int print_padding(int width, int len, char buffer[], int *index)
{
	int count;
	int i;

	count = 0;
	for (i = len; i < width; i++)
		count += buffer_char(' ', buffer, index);

	return (count);
}

int print_char(va_list args, char buffer[], int *index, char flag, char length, int width)
{
	char c;
	int count;

	(void)flag;
	(void)length;
	c = (char)va_arg(args, int);
	count = 0;
	count += print_padding(width, 1, buffer, index);
	count += buffer_char(c, buffer, index);
	return (count);
}

int print_string(va_list args, char buffer[], int *index, char flag, char length, int width)
{
	char *str;
	int count;
	int len;

	(void)flag;
	(void)length;
	str = va_arg(args, char *);
	if (!str)
		str = "(null)";

	len = 0;
	while (str[len])
		len++;

	count = 0;
	count += print_padding(width, len, buffer, index);
	while (*str)
		count += buffer_char(*str++, buffer, index);

	return (count);
}

int print_percent(va_list args, char buffer[], int *index, char flag, char length, int width)
{
	int count;

	(void)args;
	(void)flag;
	(void)length;
	count = 0;
	count += print_padding(width, 1, buffer, index);
	count += buffer_char('%', buffer, index);
	return (count);
}

int print_int(va_list args, char buffer[], int *index, char flag, char length, int width)
{
	long int n;
	unsigned long int u;
	int count;
	unsigned long int divisor;
	char sign;
	int len;
	unsigned long int tmp;

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

	if (n < 0)
		u = (unsigned long int)(-n);
	else
		u = (unsigned long int)n;

	len = 0;
	if (sign)
		len++;
	tmp = u;
	do {
		len++;
		tmp /= 10;
	} while (tmp);

	count += print_padding(width, len, buffer, index);

	if (sign)
		count += buffer_char(sign, buffer, index);

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
