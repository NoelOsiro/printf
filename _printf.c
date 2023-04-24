#include "main.h"

/**
 * _printf - Prints formatted output to stdout
 * @format: A character string containing format specifiers
 *
 * Return: The number of characters printed (excluding the null byte used to
 *         end output to strings)
 */
int _printf(const char *format, ...)
{
        int i = 0, n = 0;
        char char_arg;
        char *str_arg;
        int int_arg;
        uint32_t uint_arg;
        void *ptr_arg;
        va_list arg;

        va_start(arg, format);

        while (format && format[i])
        {
                if (format[i] == '%')
                {
                        i++;

                        switch (format[i]) {
                        case 'c':
                                char_arg = va_arg(arg, int);
                                write_char(char_arg, &n);
                                break;
                        case 's':
                                str_arg = va_arg(arg, char *);
                                write_string(str_arg, &n);
                                break;
                        case '%':
                                write_percent(&n);
                                break;
                        case 'd':
                        case 'i':
                                int_arg = va_arg(arg, int);
                                write_int(int_arg, &n);
                                break;
                        case 'u':
                                uint_arg = va_arg(arg, uint32_t);
                                write_uint(uint_arg, &n, 10, 0);
                                break;
                        case 'o':
                                uint_arg = va_arg(arg, uint32_t);
                                write_uint(uint_arg, &n, 8, 0);
                                break;
                        case 'x':
                                uint_arg = va_arg(arg, uint32_t);
                                write_uint(uint_arg, &n, 16, 0);
                                break;
                        case 'X':
                                uint_arg = va_arg(arg, uint32_t);
                                write_uint(uint_arg, &n, 16, 1);
                                break;
                        case 'S':
                                str_arg = va_arg(arg, char *);
                                write_string_special(str_arg, &n);
                                break;
                        case 'p':
                                ptr_arg = va_arg(arg, void *);
                                write_pointer(ptr_arg, &n);
                                break;
                        default:
                                write_char('%', &n);
                                write_char(format[i], &n);
                                break;
                        }
                }
                else
                {
                        write_char(format[i], &n);
                }

                i++;
        }

        va_end(arg);

        return (n);
}
