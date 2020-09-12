OBJDIR = obj/
SRCDIR = src/
INCDIR = inc/
BINDIR = bin/
CC = gcc
CFLAGS = -c -I $(INCDIR)
APP = ser

all: MAKEDIR bin/ser

#加@可以让此条命令在终端不显示
MAKEDIR:
	@mkdir -p obj/ bin/ inc/ src/

bin/ser: obj/sever.o obj/function.o
	$(CC) $^  -lsqlite3 -o $@

obj/sever.o: src/sever.c
	$(CC) $(CFLAGS) $^ -o $@

obj/function.o: src/function.c
	$(CC) $(CFLAGS) $^ -o $@


.PHONY:clean
clean:
	rm -f obj/*.o 
