#ifndef DECLAR_H
#define DECLAR_H

#include "global.h"

bool getNextToken();

void getNextChar();

void addCharToBuffer();

void clearBuffer();

void assignToken();

bool isNumber();
bool isChar();
bool isSpecial();
bool isParenthese();
bool isSymOperation();
bool isSeparator();
bool isEOF();
bool isBufferNumber();

void readNumber();
void readWord();
void readSpecial();
void readOneByOne(); 
void readSeparator();
void readUnknown();

#endif