compilateur : main.o analyseur_lexical.o analyseur_syntaxique.o
	gcc -o compilateur main.o analyseur_lexical.o analyseur_syntaxique.o

main.o : main.c global.h 
	gcc -o main.o -c main.c

analyseur_lexical.o : analyseur_lexical.c analyseur_lexical.h global.h 
	gcc -o analyseur_lexical.o -c analyseur_lexical.c

analyseur_syntaxique.o : analyseur_syntaxique.c analyseur_syntaxique.h global.h 
	gcc -o analyseur_syntaxique.o -c analyseur_syntaxique.c

clean : 
	rm -f *.exe *.o
