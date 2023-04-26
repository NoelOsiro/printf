#include "main.h"

/**
 * _printf - Prints formatted output to stdout
 * @format: A character string containing format specifiers
 *
 * Return: The number of characters printed (excluding the null byte used to
 *         end output to strings)
 */
int _printf(const char *format, ...) {
    va_list args;
    va_start(args, format);

    Buffer buf;
    init_buf(&buf);

    int len = 0;
    while (*format) {
        if (*format == '%') {
            format++;
            int flag = get_flag(&format);
            int width = get_width(&format, args);
            len += get_op(&buf, format++, args, flag | (width >= 0 ? 0 : 16)) - 1;
        } else {
            add_to_buf(&buf, *format++);
            len++;
        }
    }

    flush_buf(&buf);

    va_end(args);
    return len;
}


