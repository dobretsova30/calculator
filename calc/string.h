#pragma once

#include <string.h>
#include "token.h"
#include "polish.h"

void MyStrcpy( char* dest, char* src );
void DelSpace( char * str );
int IfDivisedOnZero( char* s );
int VerifyAlphabet( char* s );
int VerifyValidSymbols( char* s );
int VerifyE( char * s );
int VerifyPoints( char* s );