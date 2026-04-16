#include "main.h"

/**
 * print_base_unsigned - prints unsigned int using a given base
 * @n: number to print
 * @base: base characters
 * @buffer: output buffer
 * @index: current index
 *
 * Return: number of characters printed
 */
static int print_base_unsigned_inner(unsigned int n, char *base,
		char buffer[], int *index)
{
	int count;
	unsigned int base_len;

	count = 0;
	base_len = 0;
	while (base[base_len])
		base_len++;

	if (n >= base_len)
		count += print_base_unsigned_inner(n / base_len, base, buffer, index);

	count += buffer_char(base[n % base_len], buffer, index);
	return (count);
}

/**
 * print_unsigned - Handles %u specifier
 * @args: The variadic argument list
 * @buffer: output buffer
 * @index: current index
 * @flag: unused flag
 *
 * Return: Number of characters printed
 */
int print_unsigned(va_list args, char buffer[], int *index, char flag)
{
	unsigned int n;

	(void)flag;
	n = va_arg(args, unsigned int);
	return (print_base_unsigned_inner(n, "0123456789", buffer, index));
}

/**
 * print_octal - Handles %o specifier
 * @args: The variadic argument list
 * @buffer: output buffer
 * @index: current index
 * @flag: supported flag
 *
 * Return: Number of characters printed
 */
int print_octal(va_list args, char buffer[], int *index, char flag)
{
	unsigned int n;
	int count;

	n = va_arg(args, unsigned int);
	count = 0;

	if (flag == '#' && n != 0)
		count += buffer_char('0', buffer, index);

	count += print_base_unsigned_inner(n, "01234567", buffer, index);
	return (count);
}

/**
 * print_hex_lower - Handles %x specifier
 * @args: The variadic argument list
 * @buffer: output buffer
 * @index: current index
 * @flag: supported flag
 *
 * Return: Number of characters printed
 */
int print_hex_lower(va_list args, char buffer[], int *index, char flag)
{
	unsigned int n;
	int count;

	n = va_arg(args, unsigned int);
	count = 0;

	if (flag == '#' && n != 0)
	{
		count += buffer_char('0', buffer, index);
		count += buffer_char('x', buffer, index);
	}

	count += print_base_unsigned_inner(n, "0123456789abcdef", buffer, index);
	return (count);
}

/**
 * print_hex_upper - Handles %X specifier
 * @args: The variadic argument list
 * @buffer: output buffer
 * @index: current index
 * @flag: supported flag
 *
 * Return: Number of characters printed
 */
int print_hex_upper(va_list args, char buffer[], int *index, char flag)
{
	unsigned int n;
	int count;

	n = va_arg(args, unsigned int);
	count = 0;

	if (flag == '#' && n != 0)
	{
		count += buffer_char('0', buffer, index);
		count += buffer_char('X', buffer, index);
	}

	count += print_base_unsigned_inner(n, "0123456789ABCDEF", buffer, index);
	return (count);
}
