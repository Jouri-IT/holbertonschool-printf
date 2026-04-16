#include "main.h"

int print_reverse(va_list args, char buffer[], int *index,
	char flag, char length, int width, int precision)
{
	char *str;
	int len = 0, i, count = 0;

	(void)flag;
	(void)length;

	str = va_arg(args, char *);
	if (!str)
		str = "(null)";

	while (str[len])
		len++;

	if (precision >= 0 && precision < len)
		len = precision;

	if (flag == '-')
	{
		for (i = len - 1; i >= 0; i--)
			count += buffer_char(str[i], buffer, index);
		count += print_padding(width, len, buffer, index);
	}
	else
	{
		count += print_padding(width, len, buffer, index);
		for (i = len - 1; i >= 0; i--)
			count += buffer_char(str[i], buffer, index);
	}

	return (count);
}
