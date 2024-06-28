#include "include/buffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Buffer *buffer_init() {
    Buffer *buffer = malloc(sizeof(Buffer));
    buffer->data = strdup("");
    buffer->length = 0;
    return buffer;
}

void buffer_free(Buffer **pointer) {
    Buffer *buffer = *pointer;
    free(buffer->data);
    free(buffer);
    (*pointer) = NULL;
}

void buffer_write_string(Buffer *buffer, char *string) {
    buffer->length = buffer->length + strlen(string);
    buffer->data = realloc(buffer->data, sizeof(char) * buffer->length + 1);
    buffer->data = strcat(buffer->data, string);
}

void buffer_write_char(Buffer *buffer, char character) {
    buffer->length = buffer->length + 1;
    buffer->data = realloc(buffer->data, sizeof(char) * buffer->length + 1);
    char as_str[] = {character, '\0'};
    buffer->data = strcat(buffer->data, as_str);
}

char *buffer_to_string(Buffer *buffer) { return strdup(buffer->data); }

char *buffer_into_string(Buffer *buffer) {
    char *string = buffer_to_string(buffer);
    buffer_free(&buffer);
    return string;
}
