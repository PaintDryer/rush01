#Makefile
TARGET = rush01
CC = gcc
CFILES = main.c string.c board.c
CFLAGS = -Wall -Werror -Wextra

all: clean $(TARGET)

$(TARGET):
	$(CC) $(CFLAGS) -o $@ *.c

#utils
clean:
	rm -f $(TARGET)
test: all
	@#-./$(TARGET) "3 3"
	-./$(TARGET) "2 2 3 1 3 1 2 3 3 1 2 2 1 2 2 3"
	-./$(TARGET) "1 2 2 3 2 3 1 2 3 3 1 3 2 3 2 5 1 2 2 3"
	-./$(TARGET) "1 2 4 2 3 2 2 4 1 2 3 3 1 2 3 3 3 2 3 3 1 2 2 3"
	-./$(TARGET) "5 2 3 3 3 1 2 3 1 2 2 4 5 2 3 5 4 3 1 2 2 2 1 3 3 3 4 2"
	-./$(TARGET) "2 4 3 3 2 1 3 5 2 3 2 4 4 3 2 1 2 4 3 3 1 2 3 4 2 2 2 4 2 3 4 1"
	-./$(TARGET) "2 3 3 2 4 3 5 1 3 2 2 3 4 2 1 3 3 3 4 1 2 3 3 5 2 4 2 2 2 5 1 3 2 5 3 3"
.PHONY: all clean fclean re folders
