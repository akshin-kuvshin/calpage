.PHONY: all clean

TARGET = calpage
SRC = src/obj/main.o src/obj/calendar.o
CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -Werror

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

src/obj/%.o: src/%.c
	$(CC) $(CFLAGS) $< -c -o $@

clean:
	rm --recursive --force src/obj/*
	rm --force $(TARGET)
	echo ru >lang.txt
