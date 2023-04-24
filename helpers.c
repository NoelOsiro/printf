#include "main.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


char buffer[BUFFER_SIZE];

/**
 * write_char - Helper function for the 'c' case
 * @c: Character to write
 * @n: Pointer to integer keeping track of number of characters written
 *
 * Description: Writes a single character to the buffer and flushes the buffer to stdout if it's full
 */
void write_char(char c, int *n) {

    buffer[(*n)++] = (uint8_t)c;

    if (*n >= BUFFER_SIZE) {
        /* buffer full, write to stdout */  
        write(STDOUT_FILENO, buffer, BUFFER_SIZE);
        *n = 0;
    }
}


/**
 * write_string - Helper function for the 's' case
 * @str: Null-terminated string to write
 * @n: Pointer to integer keeping track of number of characters written
 *
 * Description: Writes a null-terminated string to the buffer and flushes the buffer to stdout if it's full
 */
void write_string(char *str, int *n) {
    while (*str) {
        buffer[(*n)++] = (uint8_t)(*str++);
        if (*n >= BUFFER_SIZE) {
            /* buffer full, write to stdout */
            write(STDOUT_FILENO, buffer, BUFFER_SIZE);
            *n = 0;
        }
    }
}

/**
 * write_percent - Helper function for the '%' case
 * @n: Pointer to integer keeping track of number of characters written
 *
 * Description: Writes a '%' character to the buffer and flushes the buffer to stdout if it's full
 */
void write_percent(int *n) {
    buffer[(*n)++] = '%';
    if (*n >= BUFFER_SIZE) {
         /* buffer full, write to stdout */
        write(STDOUT_FILENO, buffer, BUFFER_SIZE);
        *n = 0;
    }
}


/**
 * write_int - Helper function for the 'd' and 'i' cases
 * @n: Pointer to integer keeping track of number of characters written
 * @num: Integer to write
 *
 * Description: Writes an integer to the buffer and flushes the buffer to stdout if it's full
 */
void write_int(int arg, int *n) {
    if (arg < 0) {
        buffer[(*n)++] = '-';
        arg = -arg;
    }
    if (arg >= 10) {
        write_int(arg / 10, n);
    }
    buffer[(*n)++] = (uint8_t)((arg % 10) + '0');
    if (*n >= BUFFER_SIZE) {
         /* buffer full, write to stdout */
        write(STDOUT_FILENO, buffer, BUFFER_SIZE);
        *n = 0;
    }
}

/**
 * write_uint - Helper function for the 'u', 'o', 'x', 'X', and 'p' cases
 * @n: Pointer to integer keeping track of number of characters written
 * @num: Unsigned integer to write
 * @base: Base of the integer representation (8 for octal, 10 for decimal, 16 for hexadecimal)
 * @is_upper: Boolean indicating whether to use uppercase letters for hexadecimal (0 for lowercase, 1 for uppercase)
 * @prefix: Prefix to use for octal ('0'), hexadecimal ('0x' or '0X'), or NULL for decimal and pointer cases
 *
 * Description: Writes an unsigned integer to the buffer and flushes the buffer to stdout if it's full
 */
void write_uint(uint32_t arg, int *n, int base, int is_uppercase) {
    static const char *digits_lowercase = "0123456789abcdef";
    static const char *digits_uppercase = "0123456789ABCDEF";
    const char *digits = is_uppercase ? digits_uppercase : digits_lowercase;
    if (arg >= (uint32_t)base) {
        write_uint(arg / base, n, base, is_uppercase);
    }
    buffer[(*n)++] = (uint8_t)digits[arg % base];
    if (*n >= BUFFER_SIZE) {
         /* buffer full, write to stdout */
        write(STDOUT_FILENO, buffer, BUFFER_SIZE);
        *n = 0;
    }
}

/**
 * write_string_special - Helper function for the 'S' case
 * @str: String to write
 * @n: Pointer to integer keeping track of number of characters written
 *
 * Description: Writes a string to the buffer, replacing non-printable characters with their ASCII code value in hexadecimal
 *              and flushes the buffer to stdout if it's full.
 */
void write_string_special(char *str, int *n) {
    while (*str) {
        if (*str < ' ' || *str >= 0x7f) {
            buffer[(*n)++] = '\\';
            buffer[(*n)++] = 'x';
            buffer[(*n)++] = (*str >> 4) + '0';
            buffer[(*n)++] = ((*str & 0xf) < 10) ? ((*str & 0xf) + '0') : ((*str & 0xf) - 10 + 'A');
        } else {
            buffer[(*n)++] = (uint8_t)(*str);
        }
        if (*n >= BUFFER_SIZE) {
            /* buffer full, write to stdout */
            write(STDOUT_FILENO, buffer, BUFFER_SIZE);
            *n = 0;
        }
        str++;
    }
}
/**
 * write_pointer - Helper function for the 'p' case
 * @n: Pointer to integer keeping track of number of characters written
 * @ptr: Pointer to write
 *
 * Description: Writes a pointer to the buffer in hexadecimal format and flushes the buffer to stdout if it's full.
 */
void write_pointer(void *arg, int *n) {
    write_uint((uint32_t)(intptr_t)arg, n, 16, 0);
}
