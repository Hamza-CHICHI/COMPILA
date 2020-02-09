#ifndef DECLAR_H
#define DECLAR_H

#include "global.h"

bool getNextToken();

void getNextChar();

void addCharToBuffer();

void clearBuffer();

bool isNumber();
bool isChar();
bool isSpecial();
bool isSeparator();
bool isEOF();

void readNumber();
void readWord();
void readSpecial();
void readSeparator();
void readUnknown();

#endif