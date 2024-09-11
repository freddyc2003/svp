CC = gcc
CFLAGS = -Wall -Werror -O3
DFLAGS = -g

SRC_DIR = src
OBJ_DIR = obj
TEST_DIR = test

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

TARGET = runme
TEST_TARGET = runtest

# The main target
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(DFLAGS) -o $@ $^ -lm

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(DFLAGS) -c -o $@ $<

cpplint:
	cpplint --filter=-legal,-build $(SRC_DIR)/*.[c,h]

test: $(TARGET)
	$(CC) -o runtest $(TEST_DIR)/test.c
	./$(TEST_TARGET)
	make clean

clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET) $(TEST_TARGET)

.PHONY: all cpplint test