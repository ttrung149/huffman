#################################################################
#
#   Huffman-compressor - Trung Truong - 2019
#
#   File name: Makefile
#
#   Description: Contains Makefile targets for creating executables,
#	running setups, cleaning files, etc.
#
#################################################################

# MAKE VARIABLES
# --------------

# Uses gcc as the compiler
CC=gcc

# Updates path to header files
IFLAGS = -I/include -I/hanson/include

# Compile flags
CFLAGS = -g -std=gnu99 -Wall -Wextra -Werror -Wfatal-errors -pedantic $(IFLAGS)

# Hanson data structures
HANSON_TABLE = 	hanson/src/except.c \
				hanson/src/mem.c \
				hanson/src/table.c

HANSON_ARRAY =	hanson/src/array.c \
				hanson/src/mem.c \
				hanson/src/except.c

# Implemented data structures
PRIORITY_QUEUE = 	$(HANSON_ARRAY) \
					src/priority_queue.c

.PHONY: all clean

################################################################# 
#					EXEC targets
################################################################# 

# TARGET =
# all: $(TARGET)
clean:
	rm -f *.o *~ core

################################################################# 
#					TESTING targets
################################################################# 

test-priority-queue: $(PRIORITY_QUEUE) tests/test_priority_queue.c
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
