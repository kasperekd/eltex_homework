CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror
SRCDIR = .
BUILDDIR = build

SRCS := $(wildcard $(SRCDIR)/*.c)
BINS := $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%,$(SRCS))

all: $(BINS)

$(BUILDDIR)/%: $(SRCDIR)/%.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $@

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

clean:
	rm -rf $(BUILDDIR)