#include "main.h"
#include <stdarg.h>

int _printchar(char c, int *count);
int _putchar(char c);
int _printstr(char *s, int *count);
int _printint(int i, int *count);


/**
 * _printf - Prints a formatted string to standard output.
 * @format: A pointer to a string containing format specifiers.
 * @...: Optional arguments to be printed according to the format string.
 *
 * Return: The number of characters printed.
 */
int _printf(const char *format, ...)
{
int count;
va_list args;
va_start(args, format);


count = 0;
while (*format)
{
if (*format == '%')
{
format++;
switch (*format)
{
case 'c': {
char c = va_arg(args, int);
_printchar(c, &count);
break;
}
case 's': {
char *s = va_arg(args, char *);
_printstr(s, &count);
break;
}
case '%': {
_putchar('%');
count++;
break;
}
case 'd':
case 'i': {
int i = va_arg(args, int);
_printint(i, &count);
break;
}
}
}
else
{
_putchar(*format);
count++;
}
format++;
}
va_end(args);
return (count);
}
