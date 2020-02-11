#include "analyseur_lexical.h"
//****************************************************************************************
//Analyseur lexical functions :
//****************************************************************************************

int current_index = 0;
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
        strcpy(current_symbol.word,buffer); 
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
bool isBufferNumber()
{
    if ('0' <= buffer[0] && buffer[0] <= '9'){
        return true;
    }
    return false;
}

//_______________________________________________________________________________________
void assignToken()
{
    // Comparing the current word with each keyword
    int i;
    for (i = 0; i < TOKEN_LIST_SIZE; i++)
    {
        if (strcmp(current_symbol.word, keywords[i]) == 0)
        {
            current_symbol.code = i;
            printf("%s >\t %i : %s \n", tab_tokens[i],i, current_symbol.word);
            break;
        }
    }

    // If we couldn't find any token
    if (i == TOKEN_LIST_SIZE)
    {
        if (isBufferNumber())
        {
            current_symbol.code = NUM_TOKEN;
            printf("%s >\t %i : %s \n", tab_tokens[current_symbol.code], current_symbol.code, current_symbol.word);
        }
        else
        {
            current_symbol.code = ID_TOKEN;
            printf("%s >\t %i : %s \n", tab_tokens[current_symbol.code], current_symbol.code, current_symbol.word);
        }  
    }
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
    case '#': return true;
    default:
        return false;
    }
}


//______________________________________________________________________________________
bool isParenthese()
{
    if (next_char == '(' || next_char == ')')
    {
        return true;
    }
    return false;
}

//______________________________________________________________________________________
bool isSymOperation()
{
    if (next_char == '+' || next_char == '-' || next_char == '*' || next_char == '/')
    {
        return true;
    }
    return false;
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
    if (isParenthese()){readOneByOne();return;}
    do
    {
        addCharToBuffer();
        getNextChar();
    } while (isSpecial() && !(isParenthese()));
    
}

//______________________________________________________________________________________
void readOneByOne(){
    addCharToBuffer();
    getNextChar();
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