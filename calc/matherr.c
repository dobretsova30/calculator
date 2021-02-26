/* DATE: 29.04.19 */

#include "matherr.h"
#include "token.h"
#include "char.h"
#include "my_math.h"

int VerifyBrackets( TOKEN_T * s )
{
  int c = 0;
  while (s->type != DEFAULT)
  {
    if (s->type == LBRACKET)
      c++;
    if (s->type == RBRACKET)
      c--;

    s++;
  }

  return c;
}

MATHERR SearchErrors( TOKEN_T * arr )
{
  int i = 0, j = 0;
  
  if (VerifyBrackets(arr) != 0)
    return BRACKETS;

  if (arr[0].type == OPERATOR)
    if (arr[0].token.operation.flag!= UNARY)
      return FIRST_OPERATOR;

  /*if (ConvertToScientific(arr) == 0)
    return SCIENCE_FORM;*/

  while (arr[i].type != DEFAULT)
  {
    if (arr[i].type == FUNCTION && arr[i].token.function == SOMETHING_ELSE)
      return INCORRECT_NAME;

    if (arr[i].type == FUNCTION && arr[i + 1].type == DEFAULT)
      return UNEXPECTED_FINISH;
    if (arr[i].type == OPERATOR && arr[i + 1].type == DEFAULT)
      return UNEXPECTED_FINISH;

    //if (arr[i].token.value )

    if (arr[i].type == LBRACKET && arr[i + 1].type == RBRACKET)
      return BRACKETS;
    if (arr[i].type == RBRACKET && arr[i + 1].type == LBRACKET)
      return BRACKETS;
    if (arr[i].type == OPERATOR && arr[i + 1].type == RBRACKET)
      return BRACKETS;
    if ((i != 0) && arr[i].type == OPERATOR && arr[i].token.operation.flag == BINARY && arr[i - 1].type == LBRACKET)
      return FIRST_OPERATOR;
    if ((arr[i].type == OPERATOR && arr[i + 1].type == OPERATOR) && arr[i + 1].token.operation.flag == BINARY)
      return TWO_OPERATORS;
    if (arr[i].type == FUNCTION && arr[i + 1].type == RBRACKET)
      return BRACKETS;

    if (arr[i].type == FUNCTION && arr[i + 1].type == OPERATOR)
      return NEED_BRACKETS;
    if (arr[i].type == VALUE && arr[i + 1].token.value == PI)
      return USE_MULTIPLIER;

    if (arr[i].type == VALUE && arr[i].token.value != E && arr[i + 1].type == VALUE && arr[i + 1].token.value != E)
      return TWO_VALUES;
    if (arr[i].type == VALUE && arr[i + 1].type == VALUE && (arr[i + 2].type == OPERATOR || arr[i + 2].type == DEFAULT))
      return TWO_VALUES;


    if (arr[i].type == LBRACKET)
    {
      j = i;
      while (arr[j++].type != DEFAULT)
        if (arr[j].type != RBRACKET)
          ;

      if (arr[j].type == DEFAULT)
        return BRACKETS;
    }

    if (arr[i].type == RBRACKET)
    {
      if (i == 0)
        return BRACKETS;
      j = i;
      while (j != 0)
        if (arr[j--].type != LBRACKET)
          ;

      if (arr[j].type == DEFAULT)
        return BRACKETS;
    }

    i++;

  }
  return RIGHT_EXPRESSION;
}