#include "main.h"

/**
 * print_hex_special - prints hex value (2 digits uppercase)
 * @n: value
 * @buffer: output buffer
 * @index: current index
 *
 * Return: count
 */
static int print_hex_special(unsigned int n, char buffer[], int *index)
{
	char *hex;
	int count;

	hex = "0123456789ABCDEF";
	count = 0;

	count += buffer_char(hex[n / 16], buffer, index);
	count += buffer_char(hex[n % 16], buffer, index);

	return (count);
}

/**
 * print_S - handles %S
 * @args: variadic args
 * @buffer: output buffer
 * @index: current index
 * @flag: unused flag
 *
 * Return: count
 */
int print_S(va_list args, char buffer[], int *index, char flag)
{
	char *str;
	int count;
	unsigned char c;

	(void)flag;
	str = va_arg(args, char *);
	if (!str)
		str = "(null)";
	count = 0;

	while (*str)
	{
		c = *str;
		if (c < 32 || c >= 127)
		{
			count += buffer_char('\\', buffer, index);
			count += buffer_char('x', buffer, index);
			count += print_hex_special(c, buffer, index);
		}
		else
		{
			count += buffer_char(c, buffer, index);
		}
		str++;
	}

	return (count);
}
