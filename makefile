CC = gcc
EXEC = AsciiArtTool
OBJS = main.o AsciiArtTool.o RLEList.o
CFLAGS = -std=c99 -Wall -Itool -I. -I/home/mtm/pubic/2122b/ex1 -pedantic-errors -Werror -DNDEBUG

$(EXEC) : $(OBJS)
	$(CC) $(OBJS) -o $@
main.o: tool/main.c tool/AsciiArtTool.h RLEList.h
	$(CC) -c $(CFLAGS) $*.c
AsciiArtTool.o: tool/AsciiArtTool.c tool/AsciiArtTool.h RLEList.h
	$(CC) -c $(CFLAGS) $*.c
RLEList.o: RLEList.c RLEList.h
	$(CC) -c $(CFLAGS) $*.c
clean:
	rm -f $(OBJS) $(EXEC)