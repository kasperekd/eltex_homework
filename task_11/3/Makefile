CC = gcc
CFLAGS = -Iinclude -std=c99 -Wall -Wextra -Werror
BUILDDIR = ../build
SOURCES = src/main.c src/customer.c src/store.c src/supplier.c src/utils.c
OBJECTS = $(SOURCES:src/%.c=$(BUILDDIR)/%.o)
TARGET = $(BUILDDIR)/3

all: $(BUILDDIR) $(TARGET)

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^

$(BUILDDIR)/%.o: src/%.c | $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# clean:
# 	rm -rf $(BUILDDIR)

.PHONY: all clean
