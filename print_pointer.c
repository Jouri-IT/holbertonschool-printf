#include "main.h"

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

static int ptr_len(unsigned long int n)
{
	int len;

	len = 1;
	while (n >= 16)
	{
		n /= 16;
		len++;
	}
	return (len);
}

int print_pointer(va_list args, char buffer[], int *index,
	char flag, char length, int width, int precision)
{
	void *ptr;
	unsigned long int addr;
	int count;
	int len;

	(void)length;
	(void)precision;

	ptr = va_arg(args, void *);
	count = 0;

	if (!ptr)
	{
		if (flag == '-')
		{
			count += buffer_char('(', buffer, index);
			count += buffer_char('n', buffer, index);
			count += buffer_char('i', buffer, index);
			count += buffer_char('l', buffer, index);
			count += buffer_char(')', buffer, index);
			count += print_padding(width, 5, buffer, index);
		}
		else
		{
			count += print_padding(width, 5, buffer, index);
			count += buffer_char('(', buffer, index);
			count += buffer_char('n', buffer, index);
			count += buffer_char('i', buffer, index);
			count += buffer_char('l', buffer, index);
			count += buffer_char(')', buffer, index);
		}
		return (count);
	}

	addr = (unsigned long int)ptr;
	len = ptr_len(addr) + 2;

	if (flag == '-')
	{
		count += buffer_char('0', buffer, index);
		count += buffer_char('x', buffer, index);
		count += print_ptr_hex(addr, buffer, index);
		count += print_padding(width, len, buffer, index);
	}
	else
	{
		count += print_padding(width, len, buffer, index);
		count += buffer_char('0', buffer, index);
		count += buffer_char('x', buffer, index);
		count += print_ptr_hex(addr, buffer, index);
	}

	return (count);
}
