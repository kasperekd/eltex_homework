CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -fPIC
BUILD_DIR = build
INCLUDE = -I../include/

SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRCS))

all: $(BUILD_DIR)/libcalc.so

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDE)

$(BUILD_DIR)/libcalc.so: $(OBJS) | $(BUILD_DIR)
	$(CC) -shared -o $@ $(OBJS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)