CC = gcc
CFLAGS = -std=c99 -fno-stack-protector -no-pie
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