#include "analyseur_lexical.h"
//****************************************************************************************
//Analyseur lexical functions :
//****************************************************************************************

int current_index = 0;
//_______________________________________________________________________________________
void analyseur_lexical(){
    clearBuffer();
    getNextChar();
    int _bool = getNextToken();
    while (_bool)
    {
        _bool = getNextToken();
    }
    //display_id_tokens();
    //display_tokens();
    display_name_id_tokens();
    //printf("Fin.\n");
}
//_______________________________________________________________________________________
bool getNextToken(){
    clearBuffer();
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
        else if (isNewLine()){
            readNewLine();
        }
        else if (isComment()){
            readComment();
        }
        else if ( isEOF() ){
            current_symbol[current_index++].code = EOF_TOKEN;
            return false;
        }
        else{
            readUnknown();
        }
    }while(taille_buffer ==0);
    assignToken();
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
        if (strcmp(buffer, keywords[i]) == 0)
        {
            current_symbol[current_index].code = i;
            token = i;
            strcpy(current_symbol[current_index].word,buffer);
            break;
        }
    }

    // If we couldn't find any token
    if (i == TOKEN_LIST_SIZE)
    {
        if (isBufferNumber())
        {
            current_symbol[current_index].code = NUM_TOKEN;
            token = NUM_TOKEN;
            strcpy(current_symbol[current_index].word, buffer);
        }
        else if (buffer[0] == '\n'){
            current_symbol[current_index].code = ENTER_TOKEN;
            token = ENTER_TOKEN;
            strcpy(current_symbol[current_index].word, buffer);
        }
        else
        {
            current_symbol[current_index].code = ID_TOKEN;
            token = ID_TOKEN;
            strcpy(current_symbol[current_index].word, buffer);
        }  
    }
    current_index++;
}

//_______________________________________________________________________________________
void display_tokens(){
    printf("\n____________LES TOKEN____________\n");
    for (int i = 0; i < current_index; i++)
    {
        printf(">> %s\n",current_symbol[i].word);
    }
}

//_______________________________________________________________________________________
void display_id_tokens(){
    printf("\n____________LES CODES____________\n");
    for (int i = 0; i < current_index; i++)
    {
        printf(">> %d\n", current_symbol[i].code);
    } 
}

//_______________________________________________________________________________________
void display_name_id_tokens(){
    printf("\n____________ID NAMES____________\n");
    for (int i = 0; i < current_index; i++)
    {
        printf(">> %s\n", tab_tokens[current_symbol[i].code]);
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
    if ( ('a' <= next_char && next_char <= 'z') || ('A' <= next_char && next_char <= 'Z') )
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
    case '!': return true;
    case '&': return true;
    case '|': return true;
    case ',': return true;
    case '\"': return true;
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
    case '\r': return true;
    case '\t': return true;    
    default:
        return false;
    }
}

////______________________________________________________________________________________
bool isNewLine(){
    if (next_char == '\n'){
        return true;
    }
    return false;
}

//______________________________________________________________________________________
bool isEOF(){
    if (next_char == EOF){
        return true;
    }
    return false;
}

//______________________________________________________________________________________
bool isComment(){
    if (next_char == '#'){
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
void readNewLine(){
    do
    {
        addCharToBuffer();
        getNextChar();
    } while (isSeparator());
}

void readComment(){
    do
    {
        getNextChar();
    } while (!isNewLine());
}

//______________________________________________________________________________________
void readUnknown(){
    getNextChar();
}