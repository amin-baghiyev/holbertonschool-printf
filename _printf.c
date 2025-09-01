#include "main.h"
#include <stdarg.h>
#include <unistd.h>

/**
 * _printf - custom printf
 * @format: a character string
 *
 * Return: number of characters printed
 */
int _printf(const char *format, ...)
{
	va_list args;
	char c, *str;
	unsigned int i, j, count;

	va_start(args, format);
	count = 0;
	for (i = 0; format[i] != '\0'; i++)
	{
		if (format[i] != '%')
			write(1, &format[i], 1);
		else if (format[i + 1] != '\0' && format[i + 1] == 'c')
		{
			c = (char) va_arg(args, int);
			write(1, &c, 1);
			i++;
		}
		else if (format[i + 1] != '\0' && format[i + 1] == 's')
		{
			i++;
			str = va_arg(args, char *);
			if (str == NULL)
			{
				write(1, "(null)", 6);
				count += 6;
				continue;
			}
			for (j = 0; str[j] != '\0'; j++)
			;
			write(1, str, j);
			count += (j - 1);
		}
		else if (format[i + 1] != '\0' && format[i + 1] == '%')
		{
			i++, c = '%', write(1, &c, 1);
		}
		count++;
	}
	write(1, '\0', 1);
	va_end(args);
	return (count);
}
