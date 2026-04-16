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
  for (i = 0; in[i] && in[i] != c; i++)
   ;
  if (in[i])
   count += buffer_char(out[i], buffer, index);
  else
   count += buffer_char(c, buffer, index);
 }

 return (count);
}
