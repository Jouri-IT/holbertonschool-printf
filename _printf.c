#include "main.h"

#define BUF_SIZE 1024

static int (*get_handler(char c))(va_list, char[], int *, char)
{
	int i;
	specifier_t specs[] = {
		{'c', print_char},
		{'s', print_string},
		{'%', print_percent},
		{'d', print_int},
		{'i', print_int},
		{'b', print_binary},
		{'u', print_unsigned},
		{'o', print_octal},
		{'x', print_hex_lower},
		{'X', print_hex_upper},
		{'S', print_S},
		{'p', print_pointer},
		{0, NULL}
	};

	for (i = 0; specs[i].handler; i++)
	{
		if (specs[i].spec == c)
			return (specs[i].handler);
	}
	return (NULL);
}

static int is_flag(char c)
{
	return (c == '+' || c == ' ' || c == '#');
}

int _printf(const char *format, ...)
{
	va_list args;
	int count;
	int (*handler)(va_list, char[], int *, char);
	char buffer[BUF_SIZE];
	int buf_index;
	char flag;

	if (!format)
		return (-1);

	va_start(args, format);
	count = 0;
	buf_index = 0;

	while (*format)
	{
		if (*format != '%')
		{
			count += buffer_char(*format, buffer, &buf_index);
		}
		else
		{
			format++;
			flag = 0;

			while (is_flag(*format))
			{
				flag = *format;
				format++;
			}

			if (!*format)
			{
				va_end(args);
				return (-1);
			}

			handler = get_handler(*format);

			if (handler)
				count += handler(args, buffer, &buf_index, flag);
			else
			{
				count += buffer_char('%', buffer, &buf_index);
				if (flag)
					count += buffer_char(flag, buffer, &buf_index);
				count += buffer_char(*format, buffer, &buf_index);
			}
		}
		format++;
	}

	flush_buffer(buffer, &buf_index);
	va_end(args);
	return (count);
}
