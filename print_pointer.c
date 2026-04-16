#include "main.h"

/**
 * print_ptr_hex - prints number in hex (lowercase)
 * @n: number
 * @buffer: output buffer
 * @index: current index
 *
 * Return: count
 */
static int print_ptr_hex(unsigned long int n, char buffer[], int *index)
{
	char *hex;
	int count;

	hex = "0123456789abcdef";
	count = 0;

	if (n >= 16)
		count += print_ptr_hex(n / 16, buffer, index);

	count += buffer_char(hex[n % 16], buffer, index);
	return (count);
}

/**
 * print_pointer - handles %p
 * @args: variadic args
 * @buffer: output buffer
 * @index: current index
 * @flag: unused flag
 *
 * Return: count
 */
int print_pointer(va_list args, char buffer[], int *index, char flag)
{
	void *ptr;
	unsigned long int addr;
	int count;

	(void)flag;
	ptr = va_arg(args, void *);
	count = 0;

	if (!ptr)
	{
		count += buffer_char('(', buffer, index);
		count += buffer_char('n', buffer, index);
		count += buffer_char('i', buffer, index);
		count += buffer_char('l', buffer, index);
		count += buffer_char(')', buffer, index);
		return (count);
	}

	addr = (unsigned long int)ptr;
	count += buffer_char('0', buffer, index);
	count += buffer_char('x', buffer, index);
	count += print_ptr_hex(addr, buffer, index);

	return (count);
}
