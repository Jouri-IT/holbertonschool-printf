#include "main.h"

int print_int(va_list args, char buffer[], int *index, char flag, char length)
{
	long int n;
	unsigned long int u;
	int count = 0;
	unsigned long int divisor = 1;
	char sign = 0;

	if (length == 'l')
		n = va_arg(args, long int);
	else if (length == 'h')
		n = (short)va_arg(args, int);
	else
		n = va_arg(args, int);

	if (n < 0)
		sign = '-';
	else if (flag == '+')
		sign = '+';
	else if (flag == ' ')
		sign = ' ';

	if (sign)
		count += buffer_char(sign, buffer, index);

	if (n < 0)
		u = (unsigned long int)(-n);
	else
		u = (unsigned long int)n;

	while (u / divisor >= 10)
		divisor *= 10;

	while (divisor)
	{
		count += buffer_char('0' + (u / divisor % 10), buffer, index);
		divisor /= 10;
	}

	return (count);
}
