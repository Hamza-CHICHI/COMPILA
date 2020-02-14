compilateur : main.o analyseur_lexical.o
	gcc -o compilateur main.o analyseur_lexical.o

main.o : main.c global.H
	gcc -o main.o -c main.c

analyseur_lexical.o : analyseur_lexical.c analyseur_lexical.h
	gcc -o analyseur_lexical.o -c analyseur_lexical.c

clean : 
	rm -f *.exe *.o



