# Compiler
CC = gcc

# Compiler Flags
CFLAGS = -Wall

# Executable name
OUT = my_program

# Object Files
OBJS = List.o main.o

all: $(OBJS)
	$(CC) $(CFLAGS) -o $(OUT) $(OBJS)

# Compile List.c into List.o
List.o: List.c
	$(CC) $(CFLAGS) -c List.c

# Compile main.c into main.o
main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean:
ifeq ($(OS),Windows_NT)
	del *.o my_program.exe
else
	rm -f *.o my_program
endif

