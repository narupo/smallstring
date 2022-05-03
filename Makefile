CC := gcc
CC_FLAGS := -Wall -O2
OUT_LIB := libsmallstring.so
OUT_TEST := test

ifeq ($(OS),Windows_NT)
	OUT_LIB := libsmallstring.dll
	OUT_TEST := test.exe
endif

all: smallstring test

smallstring: smallstring.c smallstring.h 
	$(CC) $(CC_FLAGS) -shared -fPIC smallstring.c -o $(OUT_LIB)

test: test.c smallstring.c smallstring.h 
	$(CC) $(CC_FLAGS) test.c smallstring.c -o $(OUT_TEST)
