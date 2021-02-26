#pragma once

#include <stdlib.h>

#include "stack.h"
#include "token.h"
#include "parse.h"

typedef enum PRIOR
{
  MINUS_1 = 9,
  ZERO = 10,//^
  FIRST = 11,//*
  SECOND = 12,//+
  THIRD = 13//^
} PRIOR;

extern int GetPriority( TOKEN_T sym );
void Transform( TOKEN_T* arr );