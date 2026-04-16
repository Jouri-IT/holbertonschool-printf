#include "main.h"

static int print_base_unsigned_inner(unsigned long int n, char *base,
		char buffer[], int *index)
{
	int count;
	unsigned long int base_len;

	count = 0;
	base_len = 0;
	while (base[base_len])
		base_len++;

	if (n >= base_len)
		count += print_base_unsigned_inner(n / base_len, base, buffer, index);

	count += buffer_char(base[n % base_len], buffer, index);
	return (count);
}

static int unsigned_len(unsigned long int n, unsigned long int base_len)
{
	int len;

	len = 1;
	while (n >= base_len)
	{
		n /= base_len;
		len++;
	}
	return (len);
}

int print_unsigned(va_list args, char buffer[], int *index, char flag, char length, int width)
{
	unsigned long int n;
	int count;
	int len;

	(void)flag;
	if (length == 'l')
		n = va_arg(args, unsigned long int);
	else if (length == 'h')
		n = (unsigned short)va_arg(args, unsigned int);
	else
		n = va_arg(args, unsigned int);

	len = unsigned_len(n, 10);
	count = 0;
	count += print_padding(width, len, buffer, index);
	count += print_base_unsigned_inner(n, "0123456789", buffer, index);
	return (count);
}

int print_octal(va_list args, char buffer[], int *index, char flag, char length, int width)
{
	unsigned long int n;
	int count;
	int len;

	if (length == 'l')
		n = va_arg(args, unsigned long int);
	else if (length == 'h')
		n = (unsigned short)va_arg(args, unsigned int);
	else
		n = va_arg(args, unsigned int);

	len = unsigned_len(n, 8);
	if (flag == '#' && n != 0)
		len++;

	count = 0;
	count += print_padding(width, len, buffer, index);
	if (flag == '#' && n != 0)
		count += buffer_char('0', buffer, index);
	count += print_base_unsigned_inner(n, "01234567", buffer, index);
	return (count);
}

int print_hex_lower(va_list args, char buffer[], int *index, char flag, char length, int width)
{
	unsigned long int n;
	int count;
	int len;

	if (length == 'l')
		n = va_arg(args, unsigned long int);
	else if (length == 'h')
		n = (unsigned short)va_arg(args, unsigned int);
	else
		n = va_arg(args, unsigned int);

	len = unsigned_len(n, 16);
	if (flag == '#' && n != 0)
		len += 2;

	count = 0;
	count += print_padding(width, len, buffer, index);
	if (flag == '#' && n != 0)
	{
		count += buffer_char('0', buffer, index);
		count += buffer_char('x', buffer, index);
	}
	count += print_base_unsigned_inner(n, "0123456789abcdef", buffer, index);
	return (count);
}

int print_hex_upper(va_list args, char buffer[], int *index, char flag, char length, int width)
{
	unsigned long int n;
	int count;
	int len;

	if (length == 'l')
		n = va_arg(args, unsigned long int);
	else if (length == 'h')
		n = (unsigned short)va_arg(args, unsigned int);
	else
		n = va_arg(args, unsigned int);

	len = unsigned_len(n, 16);
	if (flag == '#' && n != 0)
		len += 2;

	count = 0;
	count += print_padding(width, len, buffer, index);
	if (flag == '#' && n != 0)
	{
		count += buffer_char('0', buffer, index);
		count += buffer_char('X', buffer, index);
	}
	count += print_base_unsigned_inner(n, "0123456789ABCDEF", buffer, index);
	return (count);
}
