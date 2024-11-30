CC = gcc
CFLAGS = -Wall -I./include
SRCDIR = src
OBJDIR = obj

# Source files
SOURCES = $(SRCDIR)/main.c \
          $(SRCDIR)/display.c \
          $(SRCDIR)/utils.c \
          $(SRCDIR)/algorithms/fcfs.c \
          $(SRCDIR)/algorithms/round_robin.c \
          $(SRCDIR)/algorithms/priority.c \
          $(SRCDIR)/algorithms/sjf.c \
          $(SRCDIR)/algorithms/srtf.c

# Object files
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Executable name
EXECUTABLE = scheduler

# Create object directories
$(shell mkdir -p $(OBJDIR)/algorithms)

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(EXECUTABLE)

.PHONY: all clean
