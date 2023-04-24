#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "main.h"

static void write_string(const char* str, int* n) {
    for (const char* c = str; *c; c++) {
        buffer[*n] = *c;
        (*n)++;
        if (*n >= BUFFER_SIZE) {
            // buffer full, write to stdout
            write(STDOUT_FILENO, buffer, BUFFER_SIZE);
            *n = 0;
        }
    }
}

static void write_hex(uint8_t c, int* n) {
    buffer[*n] = '\\';
    (*n)++;
    if (*n >= BUFFER_SIZE) {
        // buffer full, write to stdout
        write(STDOUT_FILENO, buffer, BUFFER_SIZE);
        *n = 0;
    }
    buffer[*n] = 'x';
    (*n)++;
    if (*n >= BUFFER_SIZE) {
        // buffer full, write to stdout
        write(STDOUT_FILENO, buffer, BUFFER_SIZE);
        *n = 0;
    }
    buffer[*n] = "0123456789ABCDEF"[c >> 4];
    (*n)++;
    if (*n >= BUFFER_SIZE) {
        // buffer full, write to stdout
        write(STDOUT_FILENO, buffer, BUFFER_SIZE);
        *n = 0;
    }
    buffer[*n] = "0123456789ABCDEF"[c & 0x0F];
    (*n)++;
    if (*n >= BUFFER_SIZE) {
        // buffer full, write to stdout
        write(STDOUT_FILENO, buffer, BUFFER_SIZE);
        *n = 0;
    }
}

// Helper function for the 's' case
void write_string(char *str, int *n) {
    while (*str) {
        buffer[(*n)++] = (uint8_t)(*str++);
        if (*n >= BUFFER_SIZE) {
            // buffer full, write to stdout
            write(STDOUT_FILENO, buffer, BUFFER_SIZE);
            *n = 0;
        }
    }
}

// Helper function for the '%' case
void write_percent(int *n) {
    buffer[(*n)++] = '%';
    if (*n >= BUFFER_SIZE) {
        // buffer full, write to stdout
        write(STDOUT_FILENO, buffer, BUFFER_SIZE);
        *n = 0;
    }
}

// Helper function for the 'd' and 'i' cases
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
        // buffer full, write to stdout
        write(STDOUT_FILENO, buffer, BUFFER_SIZE);
        *n = 0;
    }
}

// Helper function for the 'u', 'o', 'x', and 'X' cases
void write_uint(uint32_t arg, int *n, int base, int is_uppercase) {
    static const char *digits_lowercase = "0123456789abcdef";
    static const char *digits_uppercase = "0123456789ABCDEF";
    const char *digits = is_uppercase ? digits_uppercase : digits_lowercase;
    if (arg >= (uint32_t)base) {
        write_uint(arg / base, n, base, is_uppercase);
    }
    buffer[(*n)++] = (uint8_t)digits[arg % base];
    if (*n >= BUFFER_SIZE) {
        // buffer full, write to stdout
        write(STDOUT_FILENO, buffer, BUFFER_SIZE);
        *n = 0;
    }
}

// Helper function for the 'S' case
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
            // buffer full, write to stdout
            write(STDOUT_FILENO, buffer, BUFFER_SIZE);
            *n = 0;
        }
        str++;
    }
}

// Helper function for the 'p' case
void write_pointer(void *arg, int *n) {
    write_uint((uint32_t)(intptr_t)arg, n, 16, 0);
}
