#ifndef A_SYNTH_H
#define A_SYNTH_H

#include "global.h"

#define ERRORS_NUMBER 50

bool BODY();
bool INSTS();
bool INST();
bool AFFECTATION();
bool FACTEUR();
bool SI();
bool BOOLEAN();
void CONDITION();
bool OPERATION();
bool RELATION();
bool FUNCTION_DECLAR();
bool POUR();
void readEnter();
static void raise_error();
static int cpt = 0;


typedef enum errors
{
    AFFECTATION_ERROR,
    CHAR_INCONNUE_ERROR,
    PAR_OUVERTE_ERREUR,
    CONDITION_ERROR,
    PAR_FERME_ERREUR,
    INST_ERROR,
    RALATION_ERROR,
    EXPRESSION_AFTER_COND_ERROR,
    EXPRESSION_ERROR,
    TERM_ERROR,
    ACCOLADE_OUVERTE_ERROR,
    ACCOLADE_FERME_ERROR,
    FUNCTION_DECLARATION_ERROR,
    RETURN_ERROR,
    RETURN_VALUE_MISSING,
    ID_AFTER_FOR,
    DEUX_POINT_ERROR,
    IN_ERROR,
    NUM_ERROR
} error_code;

static char *tab_error[ERRORS_NUMBER] = {
    "Error in affectation",
    "Unkown Caractere",
    "Open parenthese was expected",
    "condition error",
    "Close parenthese was expected after if",
    "Instruction(s) missing",
    "Relation between expression error",
    "Expression missing after condition",
    "Unkown expression",
    "Unkown term",
    "Open braket missing",
    "Close braket missing",
    "Declaring function error",
    "function return error",
    "value was expected to be returned",
    "id was expected before in",
    "Double point was expected",
    "in was expected after id",
    "number was expected in the interval"};

#endif