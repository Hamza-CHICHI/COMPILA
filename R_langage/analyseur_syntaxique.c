#include "analyseur_syntaxique.h"

//DEBUT ANALYSEUR SYNTAXIQUE

//_________________________________________________________________________
bool BODY()
{
    readEnter();
    bool result = false;
    if (INSTS())
    {
        result = true;
    }
    return result;
}


//_________________________________________________________________________
bool INSTS()
{
    readEnter();
    if (INST())
    {
        while (INST())
        {
            ;
        }
        return true;
    }
    return false;
}

//_________________________________________________________________________
bool INST()
{
    readEnter();
    if (!AFFECTATION())
    {
        if (!SI())
        {
            if (!FUNCTION_DECLAR())
            {
                if (!POUR())
                {
                    return false;
                }
            }
        }
    }
    return true;
}

//_________________________________________________________________________
bool AFFECTATION()
{
    readEnter();
    int mycpt = cpt;
    if (current_symbol[mycpt + 2].code == FUNCTION_TOKEN || current_symbol[mycpt + 1].code == FUNCTION_TOKEN)
    {
        return false;
    }
    if (current_symbol[mycpt].code != ID_TOKEN)
    {
        if (current_symbol[mycpt].code == NUM_TOKEN && current_symbol[mycpt+1].code == AFFECTATION_TOKEN)
        {
            raise_error(AFFECTATION_ERROR);
        }
        return false;
    }
    cpt++;
    //getNextToken();
    if (current_symbol[cpt++].code == AFFECTATION_TOKEN)
    {
        //getNextToken();
        if (!FACTEUR())
        {
            raise_error(AFFECTATION_ERROR);
        }
    }
    //getNextToken();
    if (current_symbol[cpt].code != EOF_TOKEN)
    {
        cpt++;
    }
    return true;
}

//_________________________________________________________________________
bool FACTEUR()
{
    int thisToken = current_symbol[cpt].code;
    if (thisToken == ENTER_TOKEN && current_symbol[cpt - 1].code == AFFECTATION_TOKEN)
    {
        //cpt++;
        return false;
    }
    if (thisToken == EOF_TOKEN)
    {
        return false;
    }
    if (thisToken != ID_TOKEN)
    {
        if (thisToken != NUM_TOKEN)
        {
            return false;
        }
    }
    cpt++;
    if (OPERATION())
    {
        while (OPERATION())
        {
            cpt++;
            if (current_symbol[cpt].code == ID_TOKEN || current_symbol[cpt].code == NUM_TOKEN)
            {
                cpt++;
            }
            else if (current_symbol[cpt].code == ENTER_TOKEN)
            {
                raise_error(AFFECTATION_ERROR);
            }
            else
            {
                break;
            }
        }
    }
    return true;
}

//_________________________________________________________________________
bool OPERATION()
{
    int thisToken = current_symbol[cpt].code;
    switch (thisToken)
    {
    case PLUS_TOKEN:
        return true;
    case MOINS_TOKEN:
        return true;
    case MULTIPLE_TOKEN:
        return true;
    case DIVISION_TOKEN:
        return true;
    default:
        return false;
        break;
    }
}

//_________________________________________________________________________
bool SI()
{
    readEnter();
    int mycpt = cpt;
    if (current_symbol[mycpt].code != IF_TOKEN){return false;}
    cpt++;

    if (current_symbol[cpt].code != PAR_OUVERTE_TOKEN){
        if (current_symbol[cpt + 1].code == PAR_FERME_TOKEN)
        {
            cpt++;
        }
        raise_error(PAR_OUVERTE_ERREUR);
    }
    else{cpt++;}

    CONDITION();

    if (current_symbol[cpt].code != PAR_FERME_TOKEN){
        if (current_symbol[cpt + 1].code == ACCOLADE_OUVERTE_ERROR)
        {
            cpt++;
        }
        raise_error(PAR_FERME_ERREUR);
    }
    else{cpt++;}

    readEnter();

    if (current_symbol[cpt].code != ACCOLADE_OUVERTE_TOKEN){raise_error(ACCOLADE_OUVERTE_ERROR);}
    else{cpt++;}

    if (!INSTS())
    {
        raise_error(INST_ERROR);
    }
    else if (FACTEUR()){cpt++;}
    readEnter();

    if (current_symbol[cpt].code != ACCOLADE_FERME_TOKEN){raise_error(ACCOLADE_FERME_ERROR);}
    else{cpt++;}

    readEnter();
    if (current_symbol[cpt].code == ELSE_TOKEN ){
        cpt++;
        readEnter();
        if (current_symbol[cpt].code != ACCOLADE_OUVERTE_TOKEN){raise_error(ACCOLADE_OUVERTE_ERROR);}
        else{cpt++;}
        if (!INST())
        {
            raise_error(INST_ERROR);
        }
        readEnter();
        if (current_symbol[cpt].code != ACCOLADE_FERME_TOKEN){raise_error(ACCOLADE_FERME_ERROR);}
        else{cpt++;}
    }
    return true;
}

//_________________________________________________________________________
bool POUR()
{
    readEnter();
    int mycpt = cpt;
    if (current_symbol[mycpt].code != FOR_TOKEN)
    {
        return false;
    }
    cpt++;
    if (current_symbol[cpt].code != PAR_OUVERTE_TOKEN)
    {
        if (current_symbol[cpt + 1].code == ID_TOKEN)
        {
            cpt++;
        }
        raise_error(PAR_OUVERTE_ERREUR);
    }
    else
    {
        cpt++;
    }

    if (current_symbol[cpt].code != ID_TOKEN)
    {
        if (current_symbol[cpt + 1].code == IN_TOKEN)
        {
            cpt++;
        }
        raise_error(ID_AFTER_FOR);
    }
    else
    {
        cpt++;
    }

    if (current_symbol[cpt].code != IN_TOKEN)
    {
        if (current_symbol[cpt + 1].code == NUM_TOKEN)
        {
            cpt++;
        }
        raise_error(IN_ERROR);
    }
    else
    {
        cpt++;
    }

    if (current_symbol[cpt].code != NUM_TOKEN)
    {
        if (current_symbol[cpt + 1].code == DEUX_PT_TOKEN)
        {
            cpt++;
        }
        raise_error(NUM_ERROR);
    }
    else
    {
        cpt++;
    }

    if (current_symbol[cpt].code != DEUX_PT_TOKEN)
    {
        if (current_symbol[cpt + 1].code == NUM_TOKEN)
        {
            cpt++;
        }
        raise_error(DEUX_POINT_ERROR);
    }
    else
    {
        cpt++;
    }

    if (current_symbol[cpt].code != NUM_TOKEN)
    {
        if (current_symbol[cpt + 1].code == PAR_FERME_TOKEN)
        {
            cpt++;
        }
        raise_error(NUM_ERROR);
    }
    else
    {
        cpt++;
    }

    if (current_symbol[cpt].code != PAR_FERME_TOKEN)
    {
        if (current_symbol[cpt + 1].code == ACCOLADE_OUVERTE_TOKEN)
        {
            cpt++;
        }
        raise_error(PAR_OUVERTE_ERREUR);
    }
    else
    {
        cpt++;
    }
    readEnter();

    if (current_symbol[cpt].code != ACCOLADE_OUVERTE_TOKEN)
    {
        raise_error(ACCOLADE_OUVERTE_ERROR);
    }
    else
    {
        cpt++;
    }

    readEnter();
    do
    {
        ;
    } while (AFFECTATION() || SI() || POUR());
    if (current_symbol[cpt].code== NUM_TOKEN){cpt++;}

    /* if (!INSTS())
    {
        raise_error(INST_ERROR);
    } */
    readEnter();
    if (current_symbol[cpt++].code != ACCOLADE_FERME_TOKEN)
    {
        raise_error(ACCOLADE_FERME_ERROR);
    }
    return true;
}

//_________________________________________________________________________
bool FUNCTION_DECLAR()
{
    readEnter();
    int mycpt = cpt;
    if (current_symbol[mycpt].code != ID_TOKEN && (current_symbol[mycpt + 2].code != FUNCTION_TOKEN || current_symbol[mycpt + 1].code == FUNCTION_TOKEN))
    {
        return false;
    }
    cpt++;
    if (current_symbol[cpt++].code != AFFECTATION_TOKEN)
    {
        raise_error(FUNCTION_DECLARATION_ERROR);
    }
    if (current_symbol[cpt++].code != FUNCTION_TOKEN)
    {
        raise_error(FUNCTION_DECLARATION_ERROR);
    }
    if (current_symbol[cpt++].code != PAR_OUVERTE_TOKEN)
    {
        raise_error(PAR_OUVERTE_ERREUR);
    }
    if (current_symbol[cpt].code == ID_TOKEN)
    {
        do
        {
            cpt++;
        } while (current_symbol[cpt].code == ID_TOKEN || current_symbol[cpt].code == VIRGULE_TOKEN);
    }
    if (current_symbol[cpt++].code != PAR_FERME_TOKEN)
    {
        raise_error(PAR_FERME_ERREUR);
    }
    readEnter();
    if (current_symbol[cpt].code != ACCOLADE_OUVERTE_TOKEN)
    {
        raise_error(ACCOLADE_OUVERTE_ERROR);
    }
    else
    {
        cpt++;
    }
    readEnter();
    if (!INSTS())
    {
        raise_error(INST_ERROR);
    }
    else if (FACTEUR()){cpt++;}
    readEnter();
    if (current_symbol[cpt].code == RETURN_TOKEN)
    {
        cpt++;
        if (current_symbol[cpt].code != PAR_OUVERTE_TOKEN)
        {
            raise_error(RETURN_ERROR);
        }
        cpt++;
        if (current_symbol[cpt].code != ID_TOKEN)
        {
            raise_error(RETURN_VALUE_MISSING);
        }
        cpt++;
        if (current_symbol[cpt++].code != PAR_FERME_TOKEN)
        {
            raise_error(RETURN_ERROR);
        }
        readEnter();
    }
    if (current_symbol[cpt].code != ACCOLADE_FERME_TOKEN )
    {
        raise_error(ACCOLADE_FERME_ERROR);
    }
    cpt++;
    return true;
}

//_________________________________________________________________________
bool BOOLEAN()
{
    readEnter();
    int thisToken = current_symbol[cpt].code;
    if (thisToken == TRUE_TOKEN || thisToken == FALSE_TOKEN)
    {
        return true;
    }
    return false;
}

//_________________________________________________________________________
void CONDITION()
{
    readEnter();
    if (BOOLEAN())
    {
        cpt++;
    }
    else
    {
        if (!FACTEUR())
        {
            if (current_symbol[cpt].code != NEGATION_TOKEN)
            {
                raise_error(CONDITION_ERROR);
            }
        }
        if (current_symbol[cpt].code == NEGATION_TOKEN)
        {
            cpt++;
            raise_error(CONDITION_ERROR);
        }
        else
        {
            if (!RELATION())
            {
                raise_error(RALATION_ERROR);
            }
        }
        if (!FACTEUR())
        {
            raise_error(EXPRESSION_AFTER_COND_ERROR);
        }
    }
}

//_________________________________________________________________________
bool RELATION()
{
    readEnter();
    int thisToken = current_symbol[cpt++].code;
    if (thisToken != EQUAL_CONDITION_TOKEN)
    {
        if (thisToken != INF_TOKEN)
        {
            if (thisToken != INFEG_TOKEN)
            {
                if (thisToken != SUP_TOKEN)
                {
                    if (thisToken != SUPEG_TOKEN)
                    {
                        if (thisToken != DIFF_TOKEN)
                        {
                            if (thisToken != NEGATION_TOKEN)
                            {
                                if (thisToken != OR_TOKEN)
                                {
                                    if (thisToken != AND_TOKEN)
                                    {
                                        return false;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}



//_________________________________________________________________________
void readEnter()
{
    while (current_symbol[cpt].code == ENTER_TOKEN)
    {
        cpt++;
    }
}

//_________________________________________________________________________
static void raise_error(error_code ec)
{
    printf("Error number %d : %s \n", ec, tab_error[ec]);
}
