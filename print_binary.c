#include "main.h"

int print_binary(va_list args, char buffer[], int *index,
	char flag, char length, int width, int precision)
{
	unsigned int n;
	int count = 0;
	int i;
	int started = 0;

	(void)flag;
	(void)length;
	(void)width;
	(void)precision;

	n = va_arg(args, unsigned int);

	for (i = 31; i >= 0; i--)
	{
		if ((n >> i) & 1)
			started = 1;
		if (started)
			count += buffer_char(((n >> i) & 1) + '0', buffer, index);
	}

	if (!started)
		count += buffer_char('0', buffer, index);

	return (count);
}
