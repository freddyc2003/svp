CXX := gcc
CXXFLAGS := -Wall -Werror -O3
DFLAGS := -g

SRC_DIR := src
TEST_DIR := test

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:.c=.o)

TARGET := runme
TEST_TARGET := runtest

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(DFLAGS) -o $@ $^ -lm

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CXX) $(CXXFLAGS) $(DFLAGS) -c -o $@ $<

cpplint:
	cpplint --filter=-legal,-build,-readability/casting $(SRC_DIR)/*.[c,h]

test: $(TARGET)
	$(CXX) -o $(TEST_TARGET) $(TEST_DIR)/test.c
	./$(TEST_TARGET)
	make clean

clean:
	rm -f $(SRC_DIR)/*.o $(TARGET) $(TEST_TARGET)

.PHONY: all cpplint test clean
