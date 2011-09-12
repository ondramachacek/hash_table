CFLAGS=-std=c99 -pedantic -Wall
CPPFLAGS=-std=c++98 -pedantic -Wall
CC=gcc
CPP=g++

SOURCES=htable_begin.c htable_free.c htable_lookup.c htable_clear.c htable_end.c htable_init.c htable_iter_next.c

OBJS=$(SOURCES:%.c=%.o)

all: tail tail2 libhtable.a wordcount wordcount-dynamic htable.so

tail: tail.o
	$(CC) $(CFLAGS) -o tail tail.o

tail2: tail2.o
	$(CPP) $(CPPFLAGS) -o tail2 tail2.o

tail.o: tail.c
	$(CC) $(CFLAGS) -c tail.c

tail2.o: tail2.cc
	$(CPP) $(CPPFLAGS) -c tail2.cc

io.o: io.c
	$(CC) $(CFLAGS) -c io.c

wordcount: wordcount.o io.o libhtable.a
	$(CC) $(CFLAGS) -o wordcount wordcount.o io.o -lhtable -L.

wordcount-dynamic: wordcount.o io.o htable.so
	 $(CC) $(CFLAGS) -o wordcount-dynamic wordcount.o io.o htable.so

# s - ranlib, c - create, r - insert/replace
libhtable.a: $(OBJS)
	ar rcs libhtable.a $(OBJS)

htable.so: $(OBJS)
	 $(CC) $(CFLAGS) -shared -o htable.so $(OBJS) -lc
###

wordcount.o: wordcount.c
	$(CC) $(CFLAGS) -c wordcount.c
htable_init.o: htable_init.c
	$(CC) $(CFLAGS) -fPIC -c htable_init.c
htable_begin.o:htable_begin.c
	$(CC) $(CFLAGS) -fPIC -c htable_begin.c
htable_free.o: htable_free.c
	$(CC) $(CFLAGS) -fPIC -c htable_free.c
htable_lookup.o: htable_lookup.c
	$(CC) $(CFLAGS) -fPIC -c htable_lookup.c
htable_clear.o: htable_clear.c
	$(CC) $(CFLAGS) -fPIC -c htable_clear.c
htable_end.o: htable_end.c
	$(CC) $(CFLAGS) -fPIC -c htable_end.c
htable_iter_next.o: htable_iter_next.c
	$(CC) $(CFLAGS) -fPIC -c htable_iter_next.c

clean:
	rm *.o

pack:
	zip xmacha48.zip *.c *.cc *.h Makefile

libpath:
	export LD_LIBRARY_PATH=/home/Ondra/Documents/Skola/2Semestr/IJC/projekty/projekt2/wordcount/
