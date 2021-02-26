#include "string.h"
#include "char.h"

void MyStrcpy( char* dest, char* src ) 
{
  while ((*dest++ = *src++) != 0)
    ;
}

int IfDivisedOnZero( char* s )
{
  int i = 1;
  while (s[i++] != 0)
  {
    if (s[i] == '/' && s[i + 1] == '0' && IsOperation(s[i + 2]) == 1)
      return 1;
  }
  return 0;
}

void DelSpace( char* str )
{
  int i, j;
  int len = strlen(str);

  for (i = 0, j = 0; i < len; i++)
    if (!isspace(str[i]))
      str[j++] = str[i];

  str[j] = '\0';
}

int VerifyAlphabet( char* s )
{
  while (*s != 0)
  {
    if (*s > 128 && *s < 255)
      return 0;
    *s++;
  }
  return 1;
}

int VerifyValidSymbols( char* s )
{
  while (*s != 0)
  {
    if ((*s != 9 && *s < 32)|| 
      (*s >= 33 && *s <= 39) ||
      (*s == 44) ||
      (*s >= 58 && *s <= 68) ||
      (*s >= 70 && *s <= 93) ||
      (*s == 95 || *s == 96) ||
      (*s >= 123 && *s <= 127))
    {

      return 0;
    }

    *s++;
  }
  return 1;
}

int VerifyE( char * s )
{
  int i = 1;
  if (s[0] == 'E')
    return 0;
  while (s[i] != 0)
  {
    if (s[i] == 'E')
    {
      if (IsDigit(s[i - 1]) == 0)
        return 0;
    }
    i++;
  }
  return 1;
}

int VerifyPoints( char* s )
{
  int i = 1;
  if (_IsPoint(s[0]) == 1)
    return 0;
  if (IsOperation2(s[0]) == 1 && _IsPoint(s[i]) == 1)
    return 0;
  while (s[i] != 0)
  {

    if (_IsPoint(s[i]))
    {
      if ((_IsPoint(s[i - 1])) ||
        (s[i - 1] == '(')||
        (IsAlpha(s[i - 1]) == 1) ||
        (IsOperation(s[i - 1]) == 1))
        return 0;
    }
    i++;
  }
  return 1;
}