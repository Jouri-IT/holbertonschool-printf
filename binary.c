#include "main.h"

/**
 * print_binary - prints unsigned int in binary
 * @args: argument list
 * Return: count
 */
int print_binary(va_list args)
{
	unsigned int n = va_arg(args, unsigned int);
	int started = 0, count = 0, i;

	for (i = 31; i >= 0; i--)
	{
		if ((n >> i) & 1)
		{
			started = 1;
			count += write_char('1');
		}
		else if (started)
			count += write_char('0');
	}

	if (!started)
		count += write_char('0');

	return (count);
}
