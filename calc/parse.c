#include "parse.h"
#include "string.h"

TOKEN_T* Parse( char* str )
{
  int len = strlen(str);
  TOKEN_T* arr = NULL;
  TOKEN_T* r;
  char* tmp = NULL;
  int i = 0, j = 0, k = 0;
  double p;

  arr = calloc(len + 1, sizeof(TOKEN_T));
  if (arr == NULL)
  {
    /* ALARM */
    exit(MEMORY_ALLOCATION_ERROR);
  }

  r = arr;

  tmp = calloc(len + 1, sizeof(TOKEN_T));
  if (tmp == NULL)
  {
    /* ALARM */
    exit(MEMORY_ALLOCATION_ERROR);
  }

  while (*str != 0)
  {
    if (IsOperation(*str) == 1)
    {
      arr[i].token.operation.op = *str;
      arr[i].type = OPERATOR;
      i++;
    }

    else if (IsSpace(*str) == 1)
    {
      arr[i++].type = SPACE;
    }

    else if (IsDigit(*str) == 1)
    {
      for (k = 0; k < len + 1; k++)
        tmp[k] = 0;
      j = 0;
      while (IsDigit(*str) != 0)
      {

        tmp[j++] = *str++;
      }

      arr[i].token.value = atof(tmp);
      arr[i].type = VALUE;
      i++;
      *str--;
    }

    else if (IsAlpha(*str) == 1)
    {
      for (k = 0; k < len + 1; k++)
        tmp[k] = 0;
      j = 0;
      while (IsAlpha(*str) != 0)
      {

        tmp[j++] = *str++;
      }
      tmp[j] = 0;

      if (strcmp(tmp, "pi") == 0)
      {
        arr[i].token.value = PI;
        arr[i].type = VALUE;
      }

      else if ((strcmp(tmp, "e") == 0) || (strcmp(tmp, "E") == 0))
      {
        arr[i].token.value = E;
        arr[i].type = VALUE;
      }

      else
      {
        arr[i].token.function = DefineFunction(tmp);
        arr[i].type = FUNCTION;
      }

      i++;
      *str--;
    }

    else if (IsPoint(*str) == 1)
    {
      if (!IsInteger(arr[i - 1].token.value))
      {
        arr = NULL;
        free(tmp);
        free(r);
        return arr;
      }
      j = 0;
      for (k = 0; k < len + 1; k++)
        tmp[k] = 0;
      double add;
      do
      {

        tmp[j++] = *(++str);
      }
      while (IsDigit(*str) == 1);
      tmp[j - 1] = '\0';

      add = atof(tmp);
      p = pow(10, strlen(tmp));
      i--;
      arr[i++].token.value += add / p;
      *str--;
    }

    else if (IsBracket(*str) == 1)
    {
      arr[i].token.bracket = *str;
      if (arr[i].token.bracket == '(')
        arr[i].type = LBRACKET;
      else
        arr[i].type = RBRACKET;
      i++;
    }
    
    else
      ;

    *str++;
  }

  arr[i].type = DEFAULT;


  free(tmp);
  return arr;
}
