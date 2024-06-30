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

test: token_test lexer_test buffer_test ast_test parser_test evaluator_test

token_test: build_token_test
	./bin/token_test

lexer_test: build_lexer_test
	./bin/lexer_test

buffer_test: build_buffer_test
	./bin/buffer_test

ast_test: build_ast_test
	./bin/ast_test

parser_test: build_parser_test
	./bin/parser_test

evaluator_test: build_evaluator_test
	./bin/evaluator_test

build_main: $(BIN_DIR) objects
	$(CC) $(CFLAGS) -o $(BIN_DIR)/main $(addprefix $(OBJ_DIR)/, \
	token.o \
	lexer.o \
	buffer.o \
	ast.o \
	parser.o \
	evaluator.o \
	main.o)

build_token_test: $(BIN_DIR) objects
	$(CC) $(CFLAGS) -o $(BIN_DIR)/token_test $(addprefix $(OBJ_DIR)/, \
	token.o \
	lexer.o \
	buffer.o \
	ast.o \
	parser.o \
	evaluator.o \
	token_test.o)

build_lexer_test: $(BIN_DIR) objects
	$(CC) $(CFLAGS) -o $(BIN_DIR)/lexer_test $(addprefix $(OBJ_DIR)/, \
	token.o \
	lexer.o \
	buffer.o \
	ast.o \
	parser.o \
	evaluator.o \
	lexer_test.o)

build_buffer_test: $(BIN_DIR) objects
	$(CC) $(CFLAGS) -o $(BIN_DIR)/buffer_test $(addprefix $(OBJ_DIR)/, \
	token.o \
	lexer.o \
	buffer.o \
	ast.o \
	parser.o \
	evaluator.o \
	buffer_test.o)

build_ast_test: $(BIN_DIR) objects
	$(CC) $(CFLAGS) -o $(BIN_DIR)/ast_test $(addprefix $(OBJ_DIR)/, \
	token.o \
	lexer.o \
	buffer.o \
	ast.o \
	parser.o \
	evaluator.o \
	ast_test.o)

build_parser_test: $(BIN_DIR) objects
	$(CC) $(CFLAGS) -o $(BIN_DIR)/parser_test $(addprefix $(OBJ_DIR)/, \
	token.o \
	lexer.o \
	buffer.o \
	ast.o \
	parser.o \
	evaluator.o \
	parser_test.o)

build_evaluator_test: $(BIN_DIR) objects
	$(CC) $(CFLAGS) -o $(BIN_DIR)/evaluator_test $(addprefix $(OBJ_DIR)/, \
	token.o \
	lexer.o \
	buffer.o \
	ast.o \
	parser.o \
	evaluator.o \
	evaluator_test.o)

objects: $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.c -o $(OBJ_DIR)/main.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/token.c -o $(OBJ_DIR)/token.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/lexer.c -o $(OBJ_DIR)/lexer.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/buffer.c -o $(OBJ_DIR)/buffer.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/ast.c -o $(OBJ_DIR)/ast.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/parser.c -o $(OBJ_DIR)/parser.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/evaluator.c -o $(OBJ_DIR)/evaluator.o
	$(CC) $(CFLAGS) -c $(TEST_DIR)/token_test.c -o $(OBJ_DIR)/token_test.o
	$(CC) $(CFLAGS) -c $(TEST_DIR)/lexer_test.c -o $(OBJ_DIR)/lexer_test.o
	$(CC) $(CFLAGS) -c $(TEST_DIR)/buffer_test.c -o $(OBJ_DIR)/buffer_test.o
	$(CC) $(CFLAGS) -c $(TEST_DIR)/ast_test.c -o $(OBJ_DIR)/ast_test.o
	$(CC) $(CFLAGS) -c $(TEST_DIR)/parser_test.c -o $(OBJ_DIR)/parser_test.o
	$(CC) $(CFLAGS) -c $(TEST_DIR)/evaluator_test.c -o $(OBJ_DIR)/evaluator_test.o

$(OBJ_DIR):
	mkdir -p $@

$(BIN_DIR):
	mkdir -p $@

