CC=gcc
CFLAGS=-g -Wall -std=c99
EXEC=Demineur

all : $(EXEC)

Demineur : structure.o Demineur.o saisie.o io.o tadlst.o tadpro.o
	$(CC) $(CFLAGS) -o $@ $^

#GestionProfile : io.o tadlst.o tadpro.o
#	$(CC) $(CFLAGS) -c $@

%.o : GestionProfiles/%.c
	$(CC) $(CFLAGS) -c $<

%.o : %.c
	$(CC) $(CFLAGS) -c $<


.PHONY : clean run

clean :
	rm -rf *.o *~ $(EXEC)

#mrproper : clean
#	rm -rf Demineur

run : all
	./$(EXEC)
