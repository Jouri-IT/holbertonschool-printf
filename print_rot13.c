#include "main.h"

int print_rot13(va_list args, char buffer[], int *index,
	char flag, char length, int width, int precision)
{
	char *str;
	char *in;
	char *out;
	int len;
	int count;
	int i;
	int j;
	char c;

	(void)flag;
	(void)length;

	in = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	out = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(args, char *);
	if (!str)
		str = "(null)";

	len = 0;
	while (str[len])
		len++;

	if (precision >= 0 && precision < len)
		len = precision;

	count = 0;
	count += print_padding(width, len, buffer, index);

	for (i = 0; i < len; i++)
	{
		c = str[i];
		j = 0;
		while (in[j] && in[j] != c)
			j++;
		if (in[j])
			count += buffer_char(out[j], buffer, index);
		else
			count += buffer_char(c, buffer, index);
	}

	return (count);
}
