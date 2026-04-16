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

	if (n == 0)
		return (1);
	len = 0;
	while (n)
	{
		n /= base_len;
		len++;
	}
	return (len);
}

static int print_zero_padding(int width, int len, char buffer[], int *index)
{
	int count;
	int i;

	count = 0;
	for (i = len; i < width; i++)
		count += buffer_char('0', buffer, index);
	return (count);
}

int print_unsigned(va_list args, char buffer[], int *index,
	char flag, char length, int width, int precision)
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

	if (n == 0 && precision == 0)
		len = 0;
	else
		len = unsigned_len(n, 10);

	count = 0;
	if (flag == '0' && precision < 0)
		count += print_zero_padding(width, len, buffer, index);
	else
		count += print_padding(width, (precision > len ? precision : len), buffer, index);

	while (len < precision)
	{
		count += buffer_char('0', buffer, index);
		precision--;
	}

	if (!(n == 0 && len == 0))
		count += print_base_unsigned_inner(n, "0123456789", buffer, index);

	return (count);
}

int print_octal(va_list args, char buffer[], int *index,
	char flag, char length, int width, int precision)
{
	unsigned long int n;
	int count;
	int len;
	int prefix;
	int total;

	if (length == 'l')
		n = va_arg(args, unsigned long int);
	else if (length == 'h')
		n = (unsigned short)va_arg(args, unsigned int);
	else
		n = va_arg(args, unsigned int);

	if (n == 0 && precision == 0)
		len = 0;
	else
		len = unsigned_len(n, 8);

	prefix = (flag == '#' && n != 0);
	total = (precision > len ? precision : len) + prefix;
	count = 0;

	if (flag == '0' && precision < 0)
		count += print_zero_padding(width, total, buffer, index);
	else
		count += print_padding(width, total, buffer, index);

	if (prefix)
		count += buffer_char('0', buffer, index);

	while (len < precision)
	{
		count += buffer_char('0', buffer, index);
		precision--;
	}

	if (!(n == 0 && len == 0))
		count += print_base_unsigned_inner(n, "01234567", buffer, index);

	return (count);
}

int print_hex_lower(va_list args, char buffer[], int *index,
	char flag, char length, int width, int precision)
{
	unsigned long int n;
	int count;
	int len;
	int prefix;
	int total;

	if (length == 'l')
		n = va_arg(args, unsigned long int);
	else if (length == 'h')
		n = (unsigned short)va_arg(args, unsigned int);
	else
		n = va_arg(args, unsigned int);

	if (n == 0 && precision == 0)
		len = 0;
	else
		len = unsigned_len(n, 16);

	prefix = (flag == '#' && n != 0) ? 2 : 0;
	total = (precision > len ? precision : len) + prefix;
	count = 0;

	if (flag == '0' && precision < 0)
	{
		if (prefix)
		{
			count += buffer_char('0', buffer, index);
			count += buffer_char('x', buffer, index);
			prefix = 0;
			total -= 2;
			width -= 2;
		}
		count += print_zero_padding(width, total, buffer, index);
	}
	else
	{
		count += print_padding(width, total, buffer, index);
	}

	if (prefix)
	{
		count += buffer_char('0', buffer, index);
		count += buffer_char('x', buffer, index);
	}

	while (len < precision)
	{
		count += buffer_char('0', buffer, index);
		precision--;
	}

	if (!(n == 0 && len == 0))
		count += print_base_unsigned_inner(n, "0123456789abcdef", buffer, index);

	return (count);
}

int print_hex_upper(va_list args, char buffer[], int *index,
	char flag, char length, int width, int precision)
{
	unsigned long int n;
	int count;
	int len;
	int prefix;
	int total;

	if (length == 'l')
		n = va_arg(args, unsigned long int);
	else if (length == 'h')
		n = (unsigned short)va_arg(args, unsigned int);
	else
		n = va_arg(args, unsigned int);

	if (n == 0 && precision == 0)
		len = 0;
	else
		len = unsigned_len(n, 16);

	prefix = (flag == '#' && n != 0) ? 2 : 0;
	total = (precision > len ? precision : len) + prefix;
	count = 0;

	if (flag == '0' && precision < 0)
	{
		if (prefix)
		{
			count += buffer_char('0', buffer, index);
			count += buffer_char('X', buffer, index);
			prefix = 0;
			total -= 2;
			width -= 2;
		}
		count += print_zero_padding(width, total, buffer, index);
	}
	else
	{
		count += print_padding(width, total, buffer, index);
	}

	if (prefix)
	{
		count += buffer_char('0', buffer, index);
		count += buffer_char('X', buffer, index);
	}

	while (len < precision)
	{
		count += buffer_char('0', buffer, index);
		precision--;
	}

	if (!(n == 0 && len == 0))
		count += print_base_unsigned_inner(n, "0123456789ABCDEF", buffer, index);

	return (count);
}
