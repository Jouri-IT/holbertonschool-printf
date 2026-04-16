#include "main.h"

/**
 * print_binary - prints unsigned int in binary
 * @args: argument list
 * @buffer: output buffer
 * @index: current index
 * @flag: unused flag
 *
 * Return: number of characters printed
 */
int print_binary(va_list args, char buffer[], int *index, char flag)
{
	unsigned int n;
	int started;
	int count;
	int i;

	(void)flag;
	n = va_arg(args, unsigned int);
	started = 0;
	count = 0;

	for (i = 31; i >= 0; i--)
	{
		if ((n >> i) & 1)
		{
			started = 1;
			count += buffer_char('1', buffer, index);
		}
		else if (started)
		{
			count += buffer_char('0', buffer, index);
		}
	}

	if (!started)
		count += buffer_char('0', buffer, index);

	return (count);
}
