#include "errors.h"

//error tab message
static char *tab_error[ERRORS_NUMBER] = {
    "<- was expected",
};

void raise_error(error_code ec)
{
    if (ec <= ERRORS_NUMBER)
        printf("Error number %d : %s \n", ec, tab_error[ec]);
}