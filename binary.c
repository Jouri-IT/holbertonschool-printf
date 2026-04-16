#include "main.h"

/**
 * print_binary - prints unsigned int in binary
 * @args: argument list
 *
 * Return: number of characters printed
 */
int print_binary(va_list args)
{
	unsigned int n;
	int started;
	int count;
	int i;

	n = va_arg(args, unsigned int);
	started = 0;
	count = 0;

	for (i = 31; i >= 0; i--)
	{
		if ((n >> i) & 1)
		{
			started = 1;
			count += write_char('1');
		}
		else if (started)
		{
			count += write_char('0');
		}
	}

	if (!started)
		count += write_char('0');

	return (count);
}
