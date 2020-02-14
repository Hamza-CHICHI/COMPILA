#include "analyseur_lexical.h"

bool BODY() ;
bool INSTS();
bool INST();
bool AFFECTATION();
bool FACTEUR();
static void raise_error(error_code);
void getStoredToken();
int cpt = 0;

int main(int argc, char const *argv[])
{
    //Clear the console
    system("clear");

    //Ouverture du fichier :
    fichier = fopen("exemple.r", "r");

    //Analyseur lexical
    analyseur_lexical();

    //Analyseur syntaxique
    clearBuffer();
    getNextChar();
    //getNextToken();
    if (!BODY()) {printf("ERROR\n");};
    
    printf("\nFIN .\n");

    return 0;
}

//DEBUT ANALYSEUR SYNTAXIQUE

bool BODY(){
    bool result = false;
    if (INSTS()){
        result = true;
    }
    return result;
}

bool INSTS(){
    if (INST()){
        while(INST()){;}
        return true;
    }
    return false;
}

bool INST()
{
    if (!AFFECTATION()){
        return false;
    }
    return true;
}

bool AFFECTATION()
{
    if (current_symbol[cpt++].code != ID_TOKEN)
    {
        return false;
    }
    //getNextToken();
    if (current_symbol[cpt++].code == AFFECTATION_TOKEN)
    {
        //getNextToken();
        if (!FACTEUR())
        {
            raise_error(AFFECTATION_VIDE_ERROR);
        }
    }
    //getNextToken();
    current_symbol[cpt++].code;
    return true;
}

bool FACTEUR()
{
    int thisToken = current_symbol[cpt++].code;
    if (thisToken == ENTER_TOKEN){
        //getNextToken();
        current_symbol[cpt++].code;
        return false;}
    if (thisToken != ID_TOKEN)
    {
        if (thisToken != NUM_TOKEN)
        {
            if (thisToken != TRUE_TOKEN)
            {
                if (thisToken != FALSE_TOKEN)
                {
                    raise_error(CHAR_INCONNUE_ERROR);
                }
            }
        }
    }
    return true; 
}

static void raise_error(error_code ec)
{
    printf("Error number %d : %s \n", ec, tab_error[ec]);
}
