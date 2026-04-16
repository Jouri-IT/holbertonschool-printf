#include "main.h"

int print_binary(va_list args, char buffer[], int *index,
	char flag, char length, int width, int precision)
{
	unsigned int n;
	int count;
	int i;
	int started;
	int len;
	unsigned int tmp;

	(void)flag;
	(void)length;
	(void)precision;

	n = va_arg(args, unsigned int);
	len = 1;
	tmp = n;
	while (tmp > 1)
	{
		tmp >>= 1;
		len++;
	}

	count = 0;
	count += print_padding(width, len, buffer, index);

	started = 0;
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
