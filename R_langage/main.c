#include "analyseur_lexical.h"
#include "analyseur_syntaxique.h"



int main(int argc, char const *argv[])
{
    //Clear the console
    system("clear");

    //Ouverture du fichier :
    fichier = fopen("exemple.r", "r");

    //Analyseur lexical
    analyseur_lexical();

    printf("\n\n\n\n\n");

    //Analyseur syntaxique
    clearBuffer();
    getNextChar();
    //getNextToken();
    readEnter();
    if (!BODY())
    {
        printf("\nFATAL ERROR\n");
    };

    printf("\nFIN .\n");

    return 0;
}

