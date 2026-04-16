#include "main.h"

/**
 * print_hex - prints hex value (2 digits uppercase)
 */
int print_hex(unsigned int n, char buffer[], int *index)
{
	char *hex = "0123456789ABCDEF";
	int count = 0;

	count += buffer_char(hex[n / 16], buffer, index);
	count += buffer_char(hex[n % 16], buffer, index);

	return (count);
}

/**
 * print_S - handles %S
 */
int print_S(va_list args, char buffer[], int *index)
{
	char *str;
	int count = 0;
	unsigned char c;

	str = va_arg(args, char *);
	if (!str)
		str = "(null)";

	while (*str)
	{
		c = *str;

		if (c < 32 || c >= 127)
		{
			count += buffer_char('\\', buffer, index);
			count += buffer_char('x', buffer, index);
			count += print_hex(c, buffer, index);
		}
		else
		{
			count += buffer_char(c, buffer, index);
		}
		str++;
	}
	return (count);
}
