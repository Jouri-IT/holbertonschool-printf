#include "main.h"

#define BUF_SIZE 1024

/**
 * get_handler - Returns the handler for a given specifier
 * @c: The specifier character after '%'
 *
 * Return: Pointer to handler function, or NULL if not found
 */
static int (*get_handler(char c))(va_list, char[], int *)
{
	int i;
	specifier_t specs[] = {
		{'c', print_char},
		{'s', print_string},
		{'%', print_percent},
		{'d', print_int},
		{'i', print_int},
		{'b', print_binary},
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

/**
 * _printf - Produces output to stdout according to a format string
 * @format: The format string containing directives
 *
 * Return: Number of characters printed, or -1 on error
 */
int _printf(const char *format, ...)
{
	va_list args;
	int count;
	int (*handler)(va_list, char[], int *);
	char buffer[BUF_SIZE];
	int buf_index;

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
			if (!*format)
			{
				va_end(args);
				return (-1);
			}
			handler = get_handler(*format);
			if (handler)
				count += handler(args, buffer, &buf_index);
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
