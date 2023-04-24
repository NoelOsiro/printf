#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <stdint.h>

#define BUFFER_SIZE 1024
extern char buffer[BUFFER_SIZE];

int _printf(const char *format, ...);
void write_char(char c, int *n);
void write_string(char *str, int *n);
void write_percent(int *n);
void write_int(int arg, int *n);
void write_uint(uint32_t arg, int *n, int base, int is_uppercase);
void write_pointer(void *arg, int *n);
void write_string_special(char *str, int *n);

#endif /* MAIN_H */
