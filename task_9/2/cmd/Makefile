CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror
BUILD_DIR = build
LIBS = \
	../myTextPanel/build/libmyTextPanel.a \
	../myPanel/build/libmyPanel.a \
	../myUiUtils/build/libmyUiUtils.a \
	../myFileUtils/build/libmyFileUtils.a
INCLUDE = -I../include/

SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c, $(BUILD_DIR)/%.o, $(filter-out main.c, $(SRCS)))

all: $(BUILD_DIR)/main 

$(BUILD_DIR)/main: $(BUILD_DIR)/main.o $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) -o $@ $^ -lncurses

$(BUILD_DIR)/main.o: main.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(INCLUDE) $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)