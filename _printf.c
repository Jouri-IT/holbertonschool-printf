#include "main.h"

static int (*get_handler(char c))(va_list)
{
	int i;
	specifier_t specs[] = {
		{'c', print_char},
		{'s', print_string},
		{'%', print_percent},
		{0, NULL}
	};

	for (i = 0; specs[i].handler; i++)
	{
		if (specs[i].spec == c)
			return (specs[i].handler);
	}
	return (NULL);
}

int _printf(const char *format, ...)
{
	va_list args;
	int count;
	int (*handler)(va_list);

	if (!format)
		return (-1);

	va_start(args, format);
	count = 0;

	while (*format)
	{
		if (*format != '%')
		{
			count += write_char(*format);
		}
		else
		{
			format++;
			if (!*format)
				break;
			handler = get_handler(*format);
			if (handler)
				count += handler(args);
			else
			{
				count += write_char('%');
				count += write_char(*format);
			}
		}
		format++;
	}

	va_end(args);
	return (count);
}
