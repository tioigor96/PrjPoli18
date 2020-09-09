SHELL = /bin/sh

CC = gcc
CFLAGS =    -Ofast \
            --std=gnu11

CFLAG_M =   -lm

OBJ_MAIN =  obj/CLBST_s.o \
            obj/getparents.o \
            obj/graph.o

OBJ_TIME =  obj/Poli_prng.o \
            obj/timing.o

MKDIR = mkdir

all: soluzione tempi

clean:
	rm -Rf obj soluzione tempi

soluzione:          obj obj/main.o $(OBJ_MAIN)
	$(CC) obj/main.o $(OBJ_MAIN) -o $@ $(CFLAGS)

tempi:              obj obj/time.o $(OBJ_MAIN) $(OBJ_TIME)
	$(CC) obj/time.o $(OBJ_MAIN) $(OBJ_TIME) -o $@  $(CFLAG_M) $(CFLAGS)

obj:
	$(MKDIR) $@

obj/main.o:         main.c
	$(CC) -c main.c -o $@ $(CFLAGS)

obj/CLBST_s.o:      src/prj/CLBST_s.c lib/prj/CLBST_s.h
	$(CC) -c src/prj/CLBST_s.c -o $@ $(CFLAGS)

obj/getparents.o:   src/prj/getparents.c lib/prj/getparents.h
	$(CC) -c src/prj/getparents.c -o $@ $(CFLAGS)

obj/graph.o:        src/prj/graph.c lib/prj/graph.h
	$(CC) -c src/prj/graph.c -o $@ $(CFLAGS)

obj/time.o:         test/PoliReqTime/time.c
	$(CC) -c test/PoliReqTime/time.c -o $@ $(CFLAGS)

obj/Poli_prng.o:    src/timing/Poli_prng.c lib/timing/Poli_prng.h
	$(CC) -c src/timing/Poli_prng.c -o $@ $(CFLAGS) $(CFLAG_M)

obj/timing.o:       src/timing/timing.c lib/timing/timing.h
	$(CC) -c src/timing/timing.c -o $@ $(CFLAGS)
