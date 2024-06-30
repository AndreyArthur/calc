#ifndef BUFFER_H
#define BUFFER_H

#include <stddef.h>

typedef struct {
    char *data;
    size_t length;
} Buffer;

Buffer *buffer_init();

void buffer_free(Buffer **pointer);

void buffer_write_string(Buffer *buffer, char *string);

void buffer_write_char(Buffer *buffer, char character);

char *buffer_to_string(Buffer *buffer);

char *buffer_into_string(Buffer *buffer);

#endif
