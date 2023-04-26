#ifndef EOF
#define EOF (-1)
#endif

#include "main.h"
#include <stdarg.h>
#include <unistd.h>

/**
 * _putchar - Writes a character to stdout.
 * @c: The character to write.
 *
 * Return: On success, the character written. On error, -1 is returned.
 */
int _putchar(char c)
{
char ch = c;
return (write(STDOUT_FILENO, &ch, 1) == 1 ? c : EOF);
}

/**
 * _printchar - Prints a character to standard output.
 * @c: The character to print.
 * @count: A pointer to an integer that keeps track of the
 * total number of characters printed.
 *
 * Return: The number of characters printed for this character (always 1).
 */
int _printchar(char c, int *count)
{
*count += _putchar(c);
return (*count);
}

/**
 * _printstr - Prints a string to standard output.
 * @s: The string to print.
 * @count: A pointer to an integer that keeps track of
 * the total number of characters printed.
 *
 * Return: The number of characters printed for this string.
 */
int _printstr(char *s, int *count)
{
while (*s)
{
_putchar(*s++);
(*count)++;
}
return (*count);
}

/**
 * _printint - Prints an integer to standard output.
 * @i: The integer to print.
 * @count: A pointer to an integer that points to
 * of the total number of chars printed.
 *
 * Return: The number of characters printed for this integer.
 */
int _printint(int i, int *count)
{
if (i < 0)
{
_putchar('-');
(*count)++;
i = -i;
}
if (i / 10)
_printint(i / 10, count);
_putchar((i % 10) + '0');
(*count)++;
return (*count);
}
