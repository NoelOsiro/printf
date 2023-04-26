#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char buf[1024];
    size_t pos;
} Buffer;

void init_buf(Buffer *buf);
void flush_buf(Buffer *buf);
void add_to_buf(Buffer *buf, char c);
void add_str_to_buf(Buffer *buf, const char *str);
int print_int(Buffer *buf, unsigned int num, int base, bool is_unsigned, bool is_negative, int width, char pad_char);
int get_flag(const char **format);
int get_width(const char **format, va_list args);
int get_op(Buffer *buf, const char *format, va_list args, int flag);

int _printf(const char *format, ...);

#endif /* MAIN_H */
