#pragma once

#include "char.h"
#include "token.h"
#include "def.h"
#include "parse.h"
#include "string.h"
#include "polish.h"
#include "matherr.h"

int IsInteger( double x );
ANS_T Calculate( char* expression );
extern MATHERR SearchErrors( TOKEN_T * arr );