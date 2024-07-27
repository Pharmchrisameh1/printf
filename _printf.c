#include "main.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
/**
 * _printf - Build out the printf function
 * @format: string passed with possible format specifiers
 * Return: number of characters printed
 */
int _printf(const char *format, ...)
{
	int i, plen, klen;
	double totalBuffer;
	double *total;
	va_list argp;
	char buffer[BUFSIZE], *holder;
	char *(*pointer_get_valid)(va_list);

	for (i = 0; i < BUFSIZE; i++)
	{
		buffer[i] = 0;
	}
	totalBuffer = 0;
	pointer_get_valid = NULL;
	total = &totalBuffer;
	va_start(argp, format);
	for (i = plen = klen = 0; format && format[i]; i++)
	{
		if (format[i] == '%')
		{
			pointer_get_valid = get_valid_type(format[i + 1]);
			holder = (pointer_get_valid == NULL) ?
				found_nothing(format[i + 1]) :
				pointer_get_valid(argp);
			klen = _strlen(holder);
			plen = alloc_buffer(holder, klen, buffer, plen, total);
			i++;
		}
		else
		{
			holder = ctos(format[i]);
			plen = alloc_buffer(holder, 1, buffer, plen, total);
		}
	}
	va_end(argp);
	_puts(buffer, plen);
	return (totalBuffer + plen);
}
