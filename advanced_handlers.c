#include "main.h"

/**
 * print_base_unsigned - prints unsigned int using a given base
 * @n: number to print
 * @base: base characters
 *
 * Return: number of characters printed
 */
int print_base_unsigned(unsigned int n, char *base)
{
	int count;
	unsigned int base_len;

	count = 0;
	base_len = 0;
	while (base[base_len])
		base_len++;

	if (n >= base_len)
		count += print_base_unsigned(n / base_len, base);

	count += write_char(base[n % base_len]);
	return (count);
}

/**
 * print_unsigned - Handles %u specifier
 * @args: The variadic argument list
 *
 * Return: Number of characters printed
 */
int print_unsigned(va_list args)
{
	unsigned int n;

	n = va_arg(args, unsigned int);
	return (print_base_unsigned(n, "0123456789"));
}

/**
 * print_octal - Handles %o specifier
 * @args: The variadic argument list
 *
 * Return: Number of characters printed
 */
int print_octal(va_list args)
{
	unsigned int n;

	n = va_arg(args, unsigned int);
	return (print_base_unsigned(n, "01234567"));
}

/**
 * print_hex_lower - Handles %x specifier
 * @args: The variadic argument list
 *
 * Return: Number of characters printed
 */
int print_hex_lower(va_list args)
{
	unsigned int n;

	n = va_arg(args, unsigned int);
	return (print_base_unsigned(n, "0123456789abcdef"));
}

/**
 * print_hex_upper - Handles %X specifier
 * @args: The variadic argument list
 *
 * Return: Number of characters printed
 */
int print_hex_upper(va_list args)
{
	unsigned int n;

	n = va_arg(args, unsigned int);
	return (print_base_unsigned(n, "0123456789ABCDEF"));
}
