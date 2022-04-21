CC = gcc
EXEC = AsciiArtTool
OBJS = main.o AsciiArtTool.o RLEList.o
CFLAGS = -std=c99 -Wall -pedantic-errors -Werror -DNDEBUG

$(EXEC) : $(OBJS)
	$(CC) $(OBJ) -o $@
main.o: main.c AsciiArtTool.h RLEList.h
	$(CC) -c $(CFLAGS) $*.c
AsciiArtTool.o: AsciiArtTool.c AsciiArtTool.h RLEList.h
	$(CC) -c $(CFLAGS) $*.c
RLEList.o: RLEList.c RLEList.h
	$(CC) -c $(CFLAGS) $*.c
clean:
	rm -f $(OBJS) $(EXEC)