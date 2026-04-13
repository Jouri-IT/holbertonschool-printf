#include "main.h"

/**
 * write_char - Writes a single character to stdout
 * @c: The character to write
 *
 * Return: Always 1
 */
int write_char(char c)
{
	write(1, &c, 1);
	return (1);
}

/**
 * print_char - Handles %c specifier
 * @args: The variadic argument list
 *
 * Return: Number of characters printed
 */
int print_char(va_list args)
{
	char c;

	c = (char)va_arg(args, int);
	return (write_char(c));
}

/**
 * print_string - Handles %s specifier
 * @args: The variadic argument list
 *
 * Return: Number of characters printed
 */
int print_string(va_list args)
{
	char *str;
	int count;

	str = va_arg(args, char *);
	if (!str)
		str = "(null)";
	count = 0;
	while (*str)
		count += write_char(*str++);
	return (count);
}

/**
 * print_percent - Handles %% specifier
 * @args: The variadic argument list (unused)
 *
 * Return: Always 1
 */
int print_percent(va_list args)
{
	(void)args;
	return (write_char('%'));
}
