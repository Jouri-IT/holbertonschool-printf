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
			{
				va_end(args);
				return (count);
			}
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
