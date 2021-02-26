/* DATE: 22.03.19 */

#include "token.h"
#include "polish.h"
#include "my_math.h"
#include <string.h>

TYPE DefineToken( TOKEN_T token )
{
  if (token.type == VALUE)
    return VALUE;
  if (token.type == OPERATOR)
    return OPERATOR;
  if (token.type == LBRACKET)
    return LBRACKET;
  if (token.type == RBRACKET)
    return RBRACKET;
  if (token.type == FUNCTION)
    return FUNCTION;

  return DEFAULT;
}

int TokenLength( TOKEN_T* arr )
{
  int len = 0;
  while (arr++->type != DEFAULT)
    len++;
  return len;
}

void TokenCpy( TOKEN_T* Dest, TOKEN_T* Src )
{
  while (Src->type != DEFAULT)
    *Dest++ = *Src++;

  Dest->type = DEFAULT;
}

FUNC DefineFunction( char * s )
{
  if (strcmp(s, "sqrt") == 0)
    return SQRT;

  if (strcmp(s, "sin") == 0)
    return SIN;
  if (strcmp(s, "arcsin") == 0)
    return ARCSIN;

  if (strcmp(s, "cos") == 0)
    return COS;
  if (strcmp(s, "arccos") == 0)
    return ARCCOS;

  if (strcmp(s, "tg") == 0)
    return TG;
  if (strcmp(s, "arctg") == 0)
    return ARCTG;

  if (strcmp(s, "ctg") == 0)
    return CTG;
  if (strcmp(s, "arcctg") == 0)
    return ARCCTG;

  if (strcmp(s, "floor") == 0)
    return FLOOR;
  if (strcmp(s, "ceil") == 0)
    return CEIL;

  if (strcmp(s, "ln") == 0)
    return LN;

  if (strcmp(s, "log") == 0)
    return LOG;

  return SOMETHING_ELSE;
}

void TokenDelSpace( TOKEN_T * arr )
{
  int i, j;
  int len = TokenLength(arr);

  for (i = 0, j = 0; i < len; i++)
    if (arr[i].type != SPACE && arr[i].token.space != 9)
      arr[j++] = arr[i];

  arr[j].token.operation.op = '\0';
  arr[j].type = DEFAULT;
}

void TokenDefineMinus( TOKEN_T * arr )
{
  int i = 0;

  while (arr[i].type != DEFAULT)
  {
    if (arr[i].type == OPERATOR)
    {
      if (arr[i].token.operation.op == '-')
      {
        if (i == 0)
          arr[i].token.operation.flag = UNARY;
        else
        {
          if ((arr[i - 1].type == LBRACKET) || (arr[i - 1].type == OPERATOR))
            arr[i].token.operation.flag = UNARY;
          else
            if ((arr[i - 1].type == RBRACKET) || (arr[i - 1].type == VALUE ))
              arr[i].token.operation.flag = BINARY;
        }
      }
      else 
       arr[i].token.operation.flag = BINARY;
    }
    i++;
  }
}

int GetPriority( TOKEN_T sym )
{
  if (sym.type == OPERATOR)
  {
    char c = sym.token.operation.op;
    if (c == '*' || c == '/')
      return FIRST;
    if (c == '+')
      return SECOND;
    if (c == '^')
      return ZERO;

    if (c == '-')
    {
      if (sym.token.operation.flag == UNARY)
        return ZERO;
      else
        return SECOND;
    }
  }

  if (sym.type == FUNCTION)
    return MINUS_1;

  else
    return -1;
}

int ConvertToScientific( TOKEN_T * arr )
{
  int i = 0;
  while (arr[i + 1].type != DEFAULT && arr[i + 2].type != DEFAULT)
  {
    if (arr[i + 3].type != DEFAULT)
    {
      if (arr[i].type == VALUE && (arr[i + 1].type == VALUE && arr[i + 1].token.value == E))
      {
        if (arr[i + 2].type != OPERATOR && arr[i + 2].type != VALUE)
          return 0;
        if (arr[i + 2].token.operation.op == '+')
        {
          if (IsInteger(arr[i + 3].token.value) != 1)
            return 0;
          arr[i].token.value *= pow(10, arr[i + 3].token.value);
          arr[i + 1].type = SPACE;
          arr[i + 2].type = SPACE;
          arr[i + 3].type = SPACE;
        }
        if (arr[i + 2].token.operation.op == '-')
        {
          if (IsInteger(arr[i + 3].token.value) != 1)
            return 0;
          arr[i].token.value *= pow(10, (-1) * arr[i + 3].token.value);
          arr[i + 1].type = SPACE;
          arr[i + 2].type = SPACE;
          arr[i + 3].type = SPACE;
        }
      }
    }


    if (arr[i].type == VALUE && arr[i + 1].type == VALUE && arr[i + 1].token.value == E && arr[i + 2].type == VALUE)
    {
      if (IsInteger(arr[i + 2].token.value) != 1)
        return 0;
      arr[i].token.value *= pow(10, arr[i + 2].token.value);
      arr[i + 1].type = SPACE;
      arr[i + 2].type = SPACE;        
    }
    i++;
  }

  return 1;
}