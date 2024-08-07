CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror
BUILD_DIR = build
LIB_NAME = libmyTextPanel
INCLUDE = -I../include/

SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRCS))

all: $(BUILD_DIR)/$(LIB_NAME).a

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDE)

$(BUILD_DIR)/$(LIB_NAME).a: $(OBJS) | $(BUILD_DIR)
	ar rcs $@ $(OBJS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)