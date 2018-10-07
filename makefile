Démineur: structure.o 
	gcc Démineur.c -o Démineur.c
structure.o: structure.h
	gcc -c structure.c structure.h -o structure.o
clean:
	rm -rf *.o
mrproper: clean
	rm -rf Démineur