#pragma once

#include <ctype.h>

typedef enum TYPE 
{
  VALUE = 0,
  OPERATOR = 1,
  LBRACKET = 2,
  RBRACKET = 3,
  FUNCTION = 4,
  SPACE = 5,
  DEFAULT = -30
} TYPE;

typedef enum FUNCTION
{
  SQRT = 0,

  SIN = 1,
  ARCSIN = -1,

  COS = 2,
  ARCCOS = -2,

  TG = 3,
  ARCTG = -3,

  CTG = 4,
  ARCCTG = -4,

  FLOOR = 5,
  CEIL = -5,

  LN = 6,
  LOG = 7,

  SOMETHING_ELSE = 30
} FUNC;

typedef enum FLAG
{
  UNARY = 1,
  BINARY = 2
} FLAG;

typedef struct OP
{
  char op;
  FLAG flag;
} OP;

typedef union tagTOKEN
{
  double value;
  OP operation;
  char bracket;
  char space;
  FUNC function;
} TOKEN;

typedef struct _tagTOKEN {
  TOKEN token;
  TYPE type;
} TOKEN_T;

int TokenLength( TOKEN_T* arr );
TYPE DefineToken( TOKEN_T token );
void TokenCpy( TOKEN_T* Dest, TOKEN_T* Src );
FUNC DefineFunction( char * s );
void TokenDelSpace( TOKEN_T * arr );
void TokenDefineMinus( TOKEN_T * arr );
int GetPriority( TOKEN_T sym );
int ConvertToScientific( TOKEN_T * arr );