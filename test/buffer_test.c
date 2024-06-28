#include "../src/include/buffer.h"
#include <assert.h>
#include <mcheck.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_buffer_init() {
    Buffer *buffer = buffer_init();

    assert(buffer->length == 0);
    assert(buffer->data[0] == '\0');

    buffer_free(&buffer);
}

void test_buffer_free() {
    Buffer *buffer = buffer_init();
    buffer_free(&buffer);

    assert(buffer == NULL);
}

void test_buffer_write_string() {
    Buffer *buffer = buffer_init();

    buffer_write_string(buffer, "Hello, ");

    assert(buffer->length == 7);
    assert(strcmp(buffer->data, "Hello, ") == 0);

    buffer_write_string(buffer, "World!");

    assert(buffer->length == 13);
    assert(strcmp(buffer->data, "Hello, World!") == 0);

    buffer_free(&buffer);
}

void test_buffer_write_char() {
    Buffer *buffer = buffer_init();

    buffer_write_char(buffer, 'H');

    assert(buffer->length == 1);
    assert(strcmp(buffer->data, "H") == 0);

    buffer_write_char(buffer, 'i');

    assert(buffer->length == 2);
    assert(strcmp(buffer->data, "Hi") == 0);

    buffer_write_char(buffer, '!');

    assert(buffer->length == 3);
    assert(strcmp(buffer->data, "Hi!") == 0);

    buffer_free(&buffer);
}

void test_buffer_to_string() {
    Buffer *buffer = buffer_init();

    buffer_write_string(buffer, "Hello, World!");

    char *string = buffer_to_string(buffer);

    assert(strcmp(buffer->data, string) == 0);

    buffer_free(&buffer);
    free(string);
}

void test_buffer_into_string() {
    Buffer *buffer = buffer_init();

    buffer_write_string(buffer, "Hello, World!");

    char *string = buffer_into_string(buffer);

    assert(strcmp(string, "Hello, World!") == 0);

    free(string);
}

int main() {
    test_buffer_init();
    test_buffer_free();
    test_buffer_write_string();
    test_buffer_write_char();
    test_buffer_to_string();
    test_buffer_into_string();

    return 0;
}
