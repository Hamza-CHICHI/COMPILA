#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 10

//Les enums
typedef enum _bool
{
    false,
    true
} bool;

//Variables globales
char buffer[MAX_SIZE];
char next_char;
FILE *fichier ;
int taille_buffer ;

#endif