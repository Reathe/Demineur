CC=gcc
CFLAGS=-Wall -std=c99
EXEC=Démineur

all : $(EXEC)

Démineur : structure.o Démineur.o
	$(CC) $(CFLAGS) -o $@ $^

%.o : %.c
	$(CC) $(CFLAGS) -c $<

.PHONY : clean mrproper

clean :
	rm -rf *.o *~ Démineur

mrproper : clean
	rm -rf Démineur
