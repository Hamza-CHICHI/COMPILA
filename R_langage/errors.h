#ifndef ERROR_H
#define ERROR_H

#include "global.h"

#define ERRORS_NUMBER 1

typedef enum errors{
    AFFECTATION_SYMBOL_EXPECTED_ERROR,

}error_code;

void raise_error(error_code);

#endif