CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -O2
OUT = my_program

all: $(OUT)

$(OUT): main.c List.c List.h
	$(CC) $(CFLAGS) -o $@ main.c List.c

tests/test_list: tests/test_list.c List.c List.h
	$(CC) $(CFLAGS) -o $@ tests/test_list.c List.c

test: tests/test_list
	./tests/test_list

clean:
	rm -f *.o $(OUT) $(OUT).exe tests/test_list tests/test_list.exe

.PHONY: all test clean
