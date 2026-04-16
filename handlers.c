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

int print_char(va_list args, char buffer[], int *index,
	char flag, char length, int width, int precision)
{
	char c;
	int count;

	(void)flag;
	(void)length;
	(void)precision;
	c = (char)va_arg(args, int);
	count = 0;
	count += print_padding(width, 1, buffer, index);
	count += buffer_char(c, buffer, index);
	return (count);
}

int print_string(va_list args, char buffer[], int *index,
	char flag, char length, int width, int precision)
{
	char *str;
	int count;
	int len;
	int i;

	(void)flag;
	(void)length;
	str = va_arg(args, char *);
	if (!str)
		str = "(null)";

	len = 0;
	while (str[len])
		len++;

	if (precision >= 0 && precision < len)
		len = precision;

	count = 0;
	count += print_padding(width, len, buffer, index);
	for (i = 0; i < len; i++)
		count += buffer_char(str[i], buffer, index);
	return (count);
}

int print_percent(va_list args, char buffer[], int *index,
	char flag, char length, int width, int precision)
{
	int count;

	(void)args;
	(void)flag;
	(void)length;
	(void)precision;
	count = 0;
	count += print_padding(width, 1, buffer, index);
	count += buffer_char('%', buffer, index);
	return (count);
}

int print_int(va_list args, char buffer[], int *index,
	char flag, char length, int width, int precision)
{
	long int n;
	unsigned long int u;
	unsigned long int divisor;
	char sign;
	char tmp[32];
	int len;
	int count;
	int i;

	if (length == 'l')
		n = va_arg(args, long int);
	else if (length == 'h')
		n = (short)va_arg(args, int);
	else
		n = va_arg(args, int);

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

	if (u == 0 && precision == 0)
		len = 0;
	else
	{
		len = 0;
		do {
			tmp[len++] = (u % 10) + '0';
			u /= 10;
		} while (u);
	}

	while (len < precision)
		tmp[len++] = '0';

	count = 0;
	count += print_padding(width, len + (sign ? 1 : 0), buffer, index);

	if (sign)
		count += buffer_char(sign, buffer, index);

	for (i = len - 1; i >= 0; i--)
		count += buffer_char(tmp[i], buffer, index);

	(void)divisor;
	return (count);
}
