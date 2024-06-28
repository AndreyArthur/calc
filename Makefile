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

test: token_test

token_test: build_token_test
	./bin/token_test

build_main: $(BIN_DIR) objects
	$(CC) $(CFLAGS) -o $(BIN_DIR)/main $(addprefix $(OBJ_DIR)/, token.o \
	main.o)

build_token_test: $(BIN_DIR) objects
	$(CC) $(CFLAGS) -o $(BIN_DIR)/token_test $(addprefix $(OBJ_DIR)/, token.o \
	token_test.o)

objects: $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.c -o $(OBJ_DIR)/main.o && \
	$(CC) $(CFLAGS) -c $(SRC_DIR)/token.c -o $(OBJ_DIR)/token.o && \
	$(CC) $(CFLAGS) -c $(TEST_DIR)/token_test.c -o $(OBJ_DIR)/token_test.o


$(OBJ_DIR):
	mkdir -p $@

$(BIN_DIR):
	mkdir -p $@

