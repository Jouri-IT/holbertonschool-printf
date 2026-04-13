#include "main.h"

int write_char(char c)
{
	write(1, &c, 1);
	return (1);
}

int print_char(va_list args)
{
	char c;

	c = (char)va_arg(args, int);
	return (write_char(c));
}

int print_string(va_list args)
{
	char *str;
	int count;

	str = va_arg(args, char *);
	if (!str)
		str = "(null)";
	count = 0;
	while (*str)
		count += write_char(*str++);
	return (count);
}

int print_percent(va_list args)
{
	(void)args;
	return (write_char('%'));
}
