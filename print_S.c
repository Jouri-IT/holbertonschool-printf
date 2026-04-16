#include "main.h"

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

int print_S(va_list args, char buffer[], int *index, char flag, char length, int width)
{
	char *str;
	int count;
	unsigned char c;
	int len;
	char *tmp;

	(void)flag;
	(void)length;
	str = va_arg(args, char *);
	if (!str)
		str = "(null)";

	len = 0;
	tmp = str;
	while (*tmp)
	{
		c = *tmp;
		if (c < 32 || c >= 127)
			len += 4;
		else
			len++;
		tmp++;
	}

	count = 0;
	count += print_padding(width, len, buffer, index);

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
