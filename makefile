CC=gcc
CFLAGS=-g -Wall -std=c99
EXEC=Demineur

all : $(EXEC)

Demineur : structure.o Demineur.o
	$(CC) $(CFLAGS) -o $@ $^

%.o : %.c
	$(CC) $(CFLAGS) -c $<


.PHONY : clean mrproper play

clean :
	rm -rf *.o *~ Demineur

#mrproper : clean
#	rm -rf Demineur

run : all
	./Demineur
