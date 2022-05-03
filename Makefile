CC := gcc
CC_FLAGS := -Wall -O2
all: smallstring test

smallstring: smallstring.c smallstring.h 
	$(CC) $(CC_FLAGS) -shared -fPIC smallstring.c -o libsmallstring.so

test: test.c smallstring.c smallstring.h 
	$(CC) $(CC_FLAGS) test.c smallstring.c -o test
	