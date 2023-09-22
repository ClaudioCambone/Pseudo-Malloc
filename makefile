CC = gcc
CFLAGS += -Wall -Wextra -g -Wno-unused-parameter
SRC_FILES = pseudo_malloc_test.c pseudo_malloc.c my_buddy_allocator.c bit_map.c
OUTPUT = test

all: $(OUTPUT)

$(OUTPUT): $(SRC_FILES)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(OUTPUT)

run: $(OUTPUT)
	./$(OUTPUT)

.PHONY: all clean run
