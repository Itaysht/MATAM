CC = gcc
EXEC = AsciiArtTool
OBJS = tool/main.o tool/AsciiArtTool.o RLEList.o
CFLAGS = -std=c99 -Wall -Itool -I. -I/home/mtm/public/2122b/ex1 -pedantic-errors -Werror -DNDEBUG

$(EXEC) : $(OBJS)
	$(CC) $(OBJS) -o $@
RLEList.o: RLEList.c RLEList.h
	$(CC) -c $(CFLAGS) RLEList.c
/tool/AsciiArtTool.o: tool/AsciiArtTool.c tool/AsciiArtTool.h RLEList.h
	$(CC) -c $(CFLAGS) tool/AsciiArtTool.c
/tool/main.o: tool/main.c tool/AsciiArtTool.h RLEList.h
	$(CC) -c $(CFLAGS) tool/main.c
clean:
	rm -f $(OBJS) $(EXEC)