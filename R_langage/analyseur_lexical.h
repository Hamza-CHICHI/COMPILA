#ifndef A_LEX_H
#define A_LEX_H

#include "global.h"

void analyseur_lexical();

bool getNextToken();

void getNextChar();

void addCharToBuffer();

void clearBuffer();

void assignToken();

void display_tokens();

void display_id_tokens();

void display_name_id_tokens();

bool isNumber();
bool isChar();
bool isSpecial();
bool isParenthese();
bool isSymOperation();
bool isSeparator();
bool isNewLine();
bool isEOF();
bool isBufferNumber();

void readNumber();
void readWord();
void readSpecial();
void readOneByOne(); 
void readSeparator();
void readUnknown();
void readNewLine();

#endif