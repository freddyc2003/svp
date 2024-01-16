CC = gcc
CFLAGS = -Wall -Werror -O3

SRC_DIR := src
TEST_DIR := test

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:.c=.o)

TARGET := runme
TEST_TARGET := runtest

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lm

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

cpplint:
	cpplint --filter=-legal,-build $(SRC_DIR)/*.[c,h]

test: $(TARGET)
	$(CC) -o $(TEST_TARGET) $(TEST_DIR)/test.c
	./$(TEST_TARGET)
	make clean

clean:
	rm -f $(SRC_DIR)/*.o $(TARGET) $(TEST_TARGET)

.PHONY: all cpplint test clean
