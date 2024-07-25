CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror
BUILD_DIR = build
LIB_DIR = ../calc/build
LIBS = -L$(LIB_DIR) -lcalc
INCLUDE = -I../include/

SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c, $(BUILD_DIR)/%.o, $(filter-out main.c, $(SRCS)))

all: $(BUILD_DIR)/main 

$(BUILD_DIR)/main: $(BUILD_DIR)/main.o $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS) -Wl,-rpath,$(abspath $(LIB_DIR))

$(BUILD_DIR)/main.o: main.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(INCLUDE) $< -o $@

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(INCLUDE) $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)