CC=gcc
CFLAGS=-Wall -Werror -Wextra

SRC_DIR=src
OBJ_DIR=obj
BIN_DIR=bin
TEST_DIR=test

all: build_main

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

run: build_main
	./bin/main

test: token_test lexer_test buffer_test

token_test: build_token_test
	./bin/token_test

lexer_test: build_lexer_test
	./bin/lexer_test

buffer_test: build_buffer_test
	./bin/buffer_test

build_main: $(BIN_DIR) objects
	$(CC) $(CFLAGS) -o $(BIN_DIR)/main $(addprefix $(OBJ_DIR)/, \
	token.o \
	lexer.o \
	buffer.o \
	main.o)

build_token_test: $(BIN_DIR) objects
	$(CC) $(CFLAGS) -o $(BIN_DIR)/token_test $(addprefix $(OBJ_DIR)/, \
	token.o \
	lexer.o \
	buffer.o \
	token_test.o)

build_lexer_test: $(BIN_DIR) objects
	$(CC) $(CFLAGS) -o $(BIN_DIR)/lexer_test $(addprefix $(OBJ_DIR)/, \
	token.o \
	lexer.o \
	buffer.o \
	lexer_test.o)

build_buffer_test: $(BIN_DIR) objects
	$(CC) $(CFLAGS) -o $(BIN_DIR)/buffer_test $(addprefix $(OBJ_DIR)/, \
	token.o \
	lexer.o \
	buffer.o \
	buffer_test.o)

objects: $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.c -o $(OBJ_DIR)/main.o && \
	$(CC) $(CFLAGS) -c $(SRC_DIR)/token.c -o $(OBJ_DIR)/token.o && \
	$(CC) $(CFLAGS) -c $(SRC_DIR)/lexer.c -o $(OBJ_DIR)/lexer.o && \
	$(CC) $(CFLAGS) -c $(SRC_DIR)/buffer.c -o $(OBJ_DIR)/buffer.o && \
	$(CC) $(CFLAGS) -c $(TEST_DIR)/token_test.c -o $(OBJ_DIR)/token_test.o && \
	$(CC) $(CFLAGS) -c $(TEST_DIR)/lexer_test.c -o $(OBJ_DIR)/lexer_test.o
	$(CC) $(CFLAGS) -c $(TEST_DIR)/buffer_test.c -o $(OBJ_DIR)/buffer_test.o

$(OBJ_DIR):
	mkdir -p $@

$(BIN_DIR):
	mkdir -p $@

