#include "main.h"

/**
 * print_ptr_hex - prints number in hex (lowercase)
 */
int print_ptr_hex(unsigned long int n, char buffer[], int *index)
{
	char *hex = "0123456789abcdef";
	int count = 0;

	if (n >= 16)
		count += print_ptr_hex(n / 16, buffer, index);

	count += buffer_char(hex[n % 16], buffer, index);
	return (count);
}

/**
 * print_pointer - handles %p
 */
int print_pointer(va_list args, char buffer[], int *index)
{
	void *ptr;
	unsigned long int addr;
	int count = 0;

	ptr = va_arg(args, void *);

	if (!ptr)
		return (buffer_char('(', buffer, index) +
				buffer_char('n', buffer, index) +
				buffer_char('i', buffer, index) +
				buffer_char('l', buffer, index) +
				buffer_char(')', buffer, index));

	addr = (unsigned long int)ptr;

	count += buffer_char('0', buffer, index);
	count += buffer_char('x', buffer, index);

	count += print_ptr_hex(addr, buffer, index);

	return (count);
}
