#include "analyseur_lexical.h"
//****************************************************************************************
//Analyseur lexical functions :
//****************************************************************************************

//_______________________________________________________________________________________
bool getNextToken(){
    do{
        if ( isNumber() ){
            readNumber();
        }
        else if( isChar() ){
            readWord();
        }
        else if( isSpecial() ){
            readSpecial();
        }
        else if( isSeparator() ){
            readSeparator();
        }
        else if ( isEOF() ){
            return false;
        }
        else{
            readUnknown();
        }
    }while(taille_buffer ==0);

    return true; 
}

//_______________________________________________________________________________________
void getNextChar()
{
    next_char = fgetc(fichier);
}

//_______________________________________________________________________________________
void addCharToBuffer(){
    buffer[taille_buffer++] = next_char;
    buffer[taille_buffer] = '\0';
}

//_______________________________________________________________________________________
void clearBuffer(){
    taille_buffer = 0;
    buffer[taille_buffer] = '\0';
}


//_______________________________________________________________________________________
bool isNumber(){
    if ( '0' <= next_char && next_char <= '9' )
    {
        return true;
    }
    return false;
}

//______________________________________________________________________________________
bool isChar(){
    if ( ('a' <= next_char && next_char <= 'z') || ('A' <= next_char && next_char <= 'Z') || ('1' <= next_char && next_char <= '9') )
    {
        return true;
    }
    return false;
}

//______________________________________________________________________________________
bool isSpecial(){
    switch (next_char)
    {
    case '=': return true;
    case '>': return true;
    case '<': return true;
    case '*': return true;
    case '+': return true;
    case '^': return true;
    case '-': return true;
    case '%': return true;
    case '/': return true;
    case '(': return true;
    case ')': return true;
    case '{': return true;
    case '}': return true;
    case ':': return true;
    default:
        return false;
    }
}

//______________________________________________________________________________________
bool isSeparator(){
    switch (next_char)
    {
    case ' ': return true;
    case '\n': return true;
    case '\r': return true;
    case '\t': return true;    
    default:
        return false;
    }
}

//______________________________________________________________________________________
bool isEOF(){
    if (next_char == EOF){
        return true;
    }
    return false;
}

//______________________________________________________________________________________
void readNumber(){
    do
    {
        addCharToBuffer();
        getNextChar();
    } while (isNumber());
    
}

//______________________________________________________________________________________
void readWord(){
    do
    {
        addCharToBuffer();
        getNextChar();
    } while (isChar() || isNumber());
    
}

//______________________________________________________________________________________    
void readSpecial(){
    do
    {
        addCharToBuffer();
        getNextChar();
    } while (isSpecial());
    
}

//______________________________________________________________________________________
void readSeparator(){
    do
    {
        getNextChar();
    } while (isSeparator());
    
}

//______________________________________________________________________________________
void readUnknown(){
    getNextChar();
}