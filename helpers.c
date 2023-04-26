#include "main.h"
#include <unistd.h>

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 * Description: _putchar uses a local buffer of 1024 to call write
 * as little as possible
 */
int _putchar(char c)
{
	static char buf[1024];
	static int i;

	if (c == -1 || i >= 1024)
	{
		write(1, &buf, i);
		i = 0;
	}
	if (c != -1)
	{
		buf[i] = c;
		i++;
	}
	return (1);
}

/**
 * _puts - prints a string to stdout
 * @str: pointer to the string to print
 * Return: number of chars written
 */
int _puts(char *str)
{
	register int i;

	for (i = 0; str[i] != '\0'; i++)
		_putchar(str[i]);
	return (i);
}

/**
 * convert - converts number and base into string
 * @num: input number
 * @base: input base
 * @lowercase: flag if hexa values need to be lowercase
 * Return: result string
 */
char *convert(unsigned long int num, int base, int lowercase)
{
	static char *rep;
	static char buffer[50];
	char *ptr;

	rep = (lowercase)
		? "0123456789abcdef"
		: "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';
	do {
		*--ptr = rep[num % base];
		num /= base;
	} while (num != 0);

	return (ptr);
}
/**
 * get_flag - turns on flags if _printf finds
 * @s: character that holds the flag specifier
 * @f: pointer to the struct flags in which we turn the flags on
 *
 * Return: 1 if a flag has been turned on, 0 otherwise
 */
int get_flag(char s, flags_t *f)
{
int i = 0;
switch (s)
{
case '+':
f->plus = 1;
i = 1;
break;
case ' ':
f->space = 1;
i = 1;
break;
case '#':
f->hash = 1;
i = 1;
break;
}
return (i);
}

/**
 * get_print - selects the right printing function
 * depending on the conversion specifier passed to _printf
 * @s: character that holds the conversion specifier
 * Description: the function loops through the structs array
 * func_arr[] to find a match between the specifier passed to _printf
 * and the first element of the struct, and then the approriate
 * printing function
 * Return: a pointer to the matching printing function
 */
int (*get_print(char s))(va_list, flags_t *)
{
	ph func_arr[] = {
		{'i', print_int},
		{'s', print_string},
		{'c', print_char},
		{'d', print_int},
		{'u', print_unsigned},
		{'x', print_hex},
		{'X', print_hex_big},
		{'b', print_binary},
		{'o', print_octal},
		{'R', print_rot13},
		{'r', print_rev},
		{'S', print_bigS},
		{'p', print_address},
		{'%', print_percent}
		};
	int flags = 14;

	register int i;

	for (i = 0; i < flags; i++)
		if (func_arr[i].c == s)
			return (func_arr[i].f);
	return (NULL);
}

/**
 * print_address - prints address of input in hexa format
 * @l: va_list arguments from _printf
 * @f: pointer to the struct flags that determines
 * if a flag is passed to _printf
 * Return: number of char printed
 */
int print_address(va_list l, flags_t *f)
{
	char *str;
	unsigned long int p = va_arg(l, unsigned long int);

	register int count = 0;

	(void)f;

	if (!p)
		return (_puts("(nil)"));
	str = convert(p, 16, 1);
	count += _puts("0x");
	count += _puts(str);
	return (count);
}
/**
 * print_string - loops through a string and prints
 * every character
 * @l: va_list arguments from _printf
 * @f: pointer to the struct flags that determines
 * if a flag is passed to _printf
 * Return: number of char printed
 */
int print_string(va_list l, flags_t *f)
{
	char *s = va_arg(l, char *);

	(void)f;

	if (!s)
		s = "(null)";
	return (_puts(s));
}

/**
 * print_char - prints a character
 * @l: va_list arguments from _printf
 * @f: pointer to the struct flags that determines
 * if a flag is passed to _printf
 * Return: number of char printed
 */
int print_char(va_list l, flags_t *f)
{
	(void)f;
	_putchar(va_arg(l, int));
	return (1);
}

/**
 * print_hex - prints a number in hexadecimal base,
 * in lowercase
 * @l: va_list arguments from _printf
 * @f: pointer to the struct flags that determines
 * if a flag is passed to _printf
 * Description: the function calls convert() which in turns converts the input
 * number into the correct base and returns it as a string
 * Return: the number of char printed
 */
int print_hex(va_list l, flags_t *f)
{
	unsigned int num = va_arg(l, unsigned int);
	char *str = convert(num, 16, 1);
	int count = 0;

	if (f->hash == 1 && str[0] != '0')
		count += _puts("0x");
	count += _puts(str);
	return (count);
}

/**
 * print_hex_big - prints a number in hexadecimal base,
 * in uppercase
 * @l: va_list arguments from _printf
 * @f: pointer to the struct that determines
 * if a flag is passed to _printf
 * Description: the function calls convert() which in turns converts the input
 * number into the correct base and returns it as a string
 * Return: the number of char printed
 */
int print_hex_big(va_list l, flags_t *f)
{
	unsigned int num = va_arg(l, unsigned int);
	char *str = convert(num, 16, 0);
	int count = 0;

	if (f->hash == 1 && str[0] != '0')
		count += _puts("0X");
	count += _puts(str);
	return (count);
}

/**
 * print_binary - prints a number in base 2
 * @l: va_list arguments from _printf
 * @f: pointer to the struct that determines
 * if a flag is passed to _printf
 * Description: the function calls convert() which in turns converts the input
 * number into the correct base and returns it as a string
 * Return: the number of char printed
 */
int print_binary(va_list l, flags_t *f)
{
	unsigned int num = va_arg(l, unsigned int);
	char *str = convert(num, 2, 0);

	(void)f;
	return (_puts(str));
}

/**
 * print_octal - prints a number in base 8
 * @l: va_list arguments from _printf
 * @f: pointer to the struct that determines
 * if a flag is passed to _printf
 * Description: the function calls convert() which in turns converts the input
 * number into the correct base and returns it as a string
 * Return: the number of char printed
 */
int print_octal(va_list l, flags_t *f)
{
	unsigned int num = va_arg(l, unsigned int);
	char *str = convert(num, 8, 0);
	int count = 0;

	if (f->hash == 1 && str[0] != '0')
		count += _putchar('0');
	count += _puts(str);
	return (count);
}
/**
 * print_int - prints an integer
 * @l: va_list of arguments from _printf
 * @f: pointer to the struct flags determining
 * if a flag is passed to _printf
 * Return: number of char printed
 */
int print_int(va_list l, flags_t *f)
{
	int n = va_arg(l, int);
	int res = count_digit(n);

	if (f->space == 1 && f->plus == 0 && n >= 0)
		res += _putchar(' ');
	if (f->plus == 1 && n >= 0)
		res += _putchar('+');
	if (n <= 0)
		res++;
	print_number(n);
	return (res);
}

/**
 * print_unsigned - prints an unsigned integer
 * @l: va_list of arguments from _printf
 * @f: pointer to the struct flags determining
 * if a flag is passed to _printf
 * Return: number of char printed
 */
int print_unsigned(va_list l, flags_t *f)
{
	unsigned int u = va_arg(l, unsigned int);
	char *str = convert(u, 10, 0);

	(void)f;
	return (_puts(str));
}

/**
 * print_number - helper function that loops through
 * an integer and prints all its digits
 * @n: integer to be printed
 */
void print_number(int n)
{
	unsigned int n1;

	if (n < 0)
	{
		_putchar('-');
		n1 = -n;
	}
	else
		n1 = n;

	if (n1 / 10)
		print_number(n1 / 10);
	_putchar((n1 % 10) + '0');
}

/**
 * count_digit - returns the number of digits in an integer
 * for _printf
 * @i: integer to evaluate
 * Return: number of digits
 */
int count_digit(int i)
{
	unsigned int d = 0;
	unsigned int u;

	if (i < 0)
		u = i * -1;
	else
		u = i;
	while (u != 0)
	{
		u /= 10;
		d++;
	}
	return (d);
}
/**
 * print_bigS - Non printable characters
 * (0 < ASCII value < 32 or >= 127) are
 * printed this way: \x, followed by the ASCII code
 * value in hexadecimal (upper case - always 2 characters)
 * @l: va_list arguments from _printf
 * @f: pointer to the struct flags that determines
 * if a flag is passed to _printf
 * Return: number of char printed
 */
int print_bigS(va_list l, flags_t *f)
{
	int i, count = 0;
	char *res;
	char *s = va_arg(l, char *);

	(void)f;
	if (!s)
		return (_puts("(null)"));

	for (i = 0; s[i]; i++)
	{
		if (s[i] > 0 && (s[i] < 32 || s[i] >= 127))
		{
			_puts("\\x");
			count += 2;
			res = convert(s[i], 16, 0);
			if (!res[1])
				count += _putchar('0');
			count += _puts(res);
		}
		else
			count += _putchar(s[i]);
	}
	return (count);
}

/**
 * print_rev - prints a string in reverse
 * @l: argument from _printf
 * @f: pointer to the struct flags that determines
 * if a flag is passed to _printf
 * Return: length of the printed string
 */
int print_rev(va_list l, flags_t *f)
{
	int i = 0, j;
	char *s = va_arg(l, char *);

	(void)f;
	if (!s)
		s = "(null)";

	while (s[i])
		i++;

	for (j = i - 1; j >= 0; j--)
		_putchar(s[j]);

	return (i);
}

/**
 * print_rot13 - prints a string using rot13
 * @l: list of arguments from _printf
 * @f: pointer to the struct flags that determines
 * if a flag is passed to _printf
 * Return: length of the printed string
 */
int print_rot13(va_list l, flags_t *f)
{
	int i, j;
	char rot13[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char ROT13[] = "nopqrstuvwxyzabcdefghijklmNOPQRSTUVWXYZABCDEFGHIJKLM";
	char *s = va_arg(l, char *);

	(void)f;
	for (j = 0; s[j]; j++)
	{
		if (s[j] < 'A' || (s[j] > 'Z' && s[j] < 'a') || s[j] > 'z')
			_putchar(s[j]);
		else
		{
			for (i = 0; i <= 52; i++)
			{
				if (s[j] == rot13[i])
					_putchar(ROT13[i]);
			}
		}
	}

	return (j);
}

/**
 * print_percent - prints a percent
 * @l: va_list arguments from _printf
 * @f: pointer to the struct flags in which we turn the flags on
 * Return: number of char printed
 */
int print_percent(va_list l, flags_t *f)
{
	(void)l;
	(void)f;
	return (_putchar('%'));
}