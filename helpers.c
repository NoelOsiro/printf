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
