#include "analyseur_lexical.h"

int main(int argc, char const *argv[])
{
    //Clear the console
    system("clear");

    //Ouverture du fichier :
    fichier = fopen("exemple.r", "r");

    clearBuffer();
    while (getNextToken())
    {
        //printf(">> %s\n",buffer);
        assignToken();
        clearBuffer();
    }

    printf("Fin.\n");
    
    return 0;
}
