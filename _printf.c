#include "main.h"
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * int_to_str - converts string to integer
 * @integer: integer to string
 *
 * Return: string that represents integer
 */
char *int_to_str(int integer)
{
	long big_int;
	unsigned int i;
	char *str;

	big_int = integer;
	for (i = 1; integer / 10 != 0; i++)
		integer /= 10;
	if (big_int < 0)
		i++;
	str = malloc((i + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[i] = '\0';
	if (big_int < 0)
		str[0] = '-', big_int = -big_int;
	for (; i > (str[0] == '-' ? 1 : 0); i--)
		str[i - 1] = (big_int % 10) + '0', big_int /= 10;
	return (str);
}

/**
 * _strlen - retrieves length of string
 * @str: string to compute length
 *
 * Return: length of str
 */
unsigned int _strlen(char *str)
{
	unsigned int j;

	for (j = 0; str[j] != '\0'; j++)
	;
	return (j);
}

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
		if (format[i + 1] == '\0' && format[i] == '%')
			return (-1);
		if (format[i] != '%')
			write(1, &format[i], 1);
		else if (format[i + 1] == 'c')
			c = (char) va_arg(args, int), write(1, &c, 1), i++;
		else if (format[i + 1] == 's')
		{
			i++, str = va_arg(args, char *);
			if (str == NULL)
			{
				write(1, "(null)", 6), count += 6;
				continue;
			}
			j = _strlen(str), write(1, str, j), count += (j - 1);
		}
		else if (format[i + 1] == 'd' || format[i + 1] == 'i')
		{
			i++, str = int_to_str(va_arg(args, int));
			if (str == NULL)
				continue;
			j = _strlen(str), write(1, str, j), count += (j - 1), free(str);
		}
		else if (format[i + 1] == '%')
			i++, c = '%', write(1, &c, 1);
		count++;
	}
	va_end(args);
	return (count);
}
