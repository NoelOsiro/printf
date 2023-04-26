#include "main.h"

int get_flag(const char **format) {
    int flag = 0;
    while (1) {
        switch (**format) {
            case '-':
                flag |= 1;
                (*format)++;
                break;
            case '0':
                flag |= 2;
                (*format)++;
                break;
            default:
                return flag;
        }
    }
}

int get_width(const char **format, va_list args) {
    int width = 0;
    if (**format == '*') {
        width = va_arg(args, int);
        (*format)++;
    } else {
        while (isdigit(**format)) {
            width = width * 10 + (**format - '0');
            (*format)++;
        }
    }
    return width;
}
