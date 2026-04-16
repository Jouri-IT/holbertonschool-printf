#include "main.h"

int print_binary(va_list args, char buffer[], int *index, char flag, char length, int width)
{
	unsigned long int n;
	int started;
	int count;
	int i;
	int len;
	unsigned long int tmp;

	(void)flag;
	if (length == 'l')
		n = va_arg(args, unsigned long int);
	else if (length == 'h')
		n = (unsigned short)va_arg(args, unsigned int);
	else
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
	for (i = (sizeof(unsigned long int) * 8) - 1; i >= 0; i--)
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
