CXX := gcc
CXXFLAGS := -Wall -Werror -g -O3

SRC_DIR := src
OBJ_DIR := obj
TEST_DIR := test

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

TARGET := runme
TEST_TARGET := runtest

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lm

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CXX) $(CXXFLAGS) -c -o $@ $<

cpplint:
	cpplint --filter=-legal,-build,-readability/casting $(SRC_DIR)/*.c $(SRC_DIR)/*.h

test:
	$(CXX) -o runtest test/test.c
	./$(TEST_TARGET)
	make clean

clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET) $(TEST_TARGET)


.PHONY: all cpplint test