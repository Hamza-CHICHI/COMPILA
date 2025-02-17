#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 10
#define TOKEN_LIST_SIZE 100
#define MAX_FILE_TOKEN 1000

//ENUM DEFENITION
typedef enum _bool
{
    false,
    true
} bool;


typedef enum
{
    ID_TOKEN,
    NUM_TOKEN,

    //TOKEN LANGAGE
    FOR_TOKEN,
    IN_TOKEN,
    WHILE_TOKEN,
    REPEAT_TOKEN,
    BREAK_TOKEN,
    IF_TOKEN,
    ELSE_TOKEN,
    TRUE_TOKEN,
    FALSE_TOKEN,
    RETURN_TOKEN,

    //FUNCTIONS
    EXPO_TOKEN,
    LENGTH_TOKEN,
    MIN_TOKEN,
    MAX_TOKEN,
    FACTORIAL_TOKEN,
    FUNCTION_TOKEN,

    //SYMBOLE TOKEN
    PLUS_TOKEN,
    MOINS_TOKEN,
    MULTIPLE_TOKEN,
    DIVISION_TOKEN,
    EQUAL_TOKEN,
    VIRGULE_TOKEN,
    MODULO_TOKEN,
    PUISSANCE_TOKEN,

    AND_TOKEN,
    OR_TOKEN,

    INF_TOKEN,
    INFEG_TOKEN,
    SUP_TOKEN,
    SUPEG_TOKEN,
    DIFF_TOKEN,
    EQUAL_CONDITION_TOKEN,
    PAR_OUVERTE_TOKEN,
    PAR_FERME_TOKEN,
    AFFECTATION_TOKEN,
    NEGATION_TOKEN,

    ACCOLADE_OUVERTE_TOKEN,
    ACCOLADE_FERME_TOKEN,
    DEUX_PT_TOKEN,
    DOUBLEGUILLEMET_TOKEN,

    //SPECIAL TOKEN
    COMMENTAIRE_TOKEN,
    ERR_TOKEN,
    ENTER_TOKEN,
    EOF_TOKEN
} tokens;

//TABLEAU
static char tab_tokens[TOKEN_LIST_SIZE][50] = {
    "ID_TOKEN",
    "NUM_TOKEN",

    "FOR_TOKEN",
    "IN_TOKEN",
    "WHILE_TOKEN",
    "REPEAT_TOKEN",
    "BREAK_TOKEN",
    "IF_TOKEN",
    "ELSE_TOKEN",
    "TRUE_TOKEN",
    "FALSE_TOKEN",
    "RETURN_TOKEN",

    "EXPO_TOKEN",
    "LENGTH_TOKEN",
    "MIN_TOKEN",
    "MAX_TOKEN",
    "FACTORIAL_TOKEN",
    "FUNCTION_TOKEN",

    "PLUS_TOKEN",
    "MOINS_TOKEN",
    "MULTIPLE_TOKEN",
    "DIVISION_TOKEN",
    "EQUAL_TOKEN",
    "VIRGULE_TOKEN",
    "MODULO_TOKEN",
    "PUISSANCE_TOKEN",

    "AND_TOKEN",
    "OR_TOKEN",

    "INF_TOKEN",
    "INFEG_TOKEN",
    "SUP_TOKEN",
    "SUPEG_TOKEN",
    "DIFF_TOKEN",
    "EQUAL_CONDITION_TOKEN",
    "PAR_OUVERTE_TOKEN",
    "PAR_FERME_TOKEN",
    "AFFECTATION_TOKEN",
    "NEGATION_TOKEN",

    "ACCOLADE_OUVERTE_TOKEN",
    "ACCOLADE_FERME_TOKEN",
    "DEUX_PT_TOKEN",
    "DOUBLEGUILLEMET_TOKEN",

    "COMMENTAIRE_TOKEN",
    "ERR_TOKEN",
    "ENTER_TOKEN",
    "EOF_TOKEN"};

static char keywords[TOKEN_LIST_SIZE][20] = {
    "ID_TOKEN",
    "NUM_TOKEN",

    "for",
    "in",
    "while",
    "repeat",
    "break",
    "if",
    "else",
    "TRUE",
    "FALSE",
    "return",

    "exp",
    "length",
    "min",
    "max",
    "factorial",
    "function",

    "+",
    "-",
    "*",
    "/",
    "=",
    ",",
    "\%\%",
    "^",

    "&&",
    "||",

    "<",
    "<=",
    ">",
    ">=",
    "!=",
    "==",
    "(",
    ")",
    "<-",
    "!",

    "{",
    "}",
    ":",
    "\"",

    "##",
    "ERR_TOKEN",
    "\n",
    "EOF_TOKEN"};

//declaration des structures_____________________________________________________________
typedef struct symbol
{
    tokens code;
    char word[MAX_SIZE];
}symbol;

//Variables globales
char buffer[MAX_SIZE];
char next_char;
FILE *fichier ;
int taille_buffer ;
int token;

struct symbol current_symbol[MAX_FILE_TOKEN];

#endif