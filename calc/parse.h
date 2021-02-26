#pragma once

#include "token.h"
#include "def.h"
#include "char.h"

#include <math.h>

TOKEN_T* Parse( char* str );

extern int IsInteger( double x );