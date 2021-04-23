CC = gcc
FLAGS = -std=c99 -Wall -pedantic
DEPS = main.o regex.o

.PHONY: all clean

all: regex clean
regex: $(DEPS)
	$(CC) $(FLAGS) -o $@ $(DEPS)
.c.o:
	$(CC) $(FLAGS) -c -o $@ $<
clean:
	rm -f prog $(DEPS)

