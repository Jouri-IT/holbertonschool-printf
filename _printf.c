#include "main.h"

#define BUF_SIZE 1024

static int (*get_handler(char c))(va_list, char[], int *, char, char)
{
	int i;
	specifier_t specs[] = {
		{'d', print_int},
		{'i', print_int},
		{'u', print_unsigned},
		{'o', print_octal},
		{'x', print_hex_lower},
		{'X', print_hex_upper},
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

static int is_length(char c)
{
	return (c == 'l' || c == 'h');
}

int _printf(const char *format, ...)
{
	va_list args;
	int count = 0;
	int (*handler)(va_list, char[], int *, char, char);
	char buffer[BUF_SIZE];
	int buf_index = 0;
	char flag;
	char length;

	if (!format)
		return (-1);

	va_start(args, format);

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
			length = 0;

			while (is_flag(*format))
			{
				if (*format == '+')
					flag = '+';
				else if (*format == ' ' && flag != '+')
					flag = ' ';
				else if (*format == '#' && flag == 0)
					flag = '#';
				format++;
			}

			if (is_length(*format))
			{
				length = *format;
				format++;
			}

			if (!*format)
			{
				va_end(args);
				return (-1);
			}

			handler = get_handler(*format);

			if (handler)
				count += handler(args, buffer, &buf_index, flag, length);
			else
			{
				count += buffer_char('%', buffer, &buf_index);
				count += buffer_char(*format, buffer, &buf_index);
			}
		}
		format++;
	}

	flush_buffer(buffer, &buf_index);
	va_end(args);
	return (count);
}
