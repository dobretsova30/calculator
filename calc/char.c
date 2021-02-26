#include "char.h"

int IsOperation( char c )
{
  if (c == '+' || 
    c == '-' ||
    c == '*' ||
    c == '/' ||
    c == '^')
    return 1;
  return 0;
}

int IsOperation2( char c )
{
  if (c == '+' || 
    c == '*' ||
    c == '/' ||
    c == '^')
    return 1;
  return 0;
}

int IsDigit( char c )
{
  if (isdigit(c))
    return 1;
  return 0;
}

int IsAlpha( char c )
{
  if (isalpha(c))
    return 1;
  return 0;
}

int IsPoint( char c )
{
  if (c == '.')
    return 1;
  return 0;
}

int IsBracket( char c )
{
  if (c == '(' || c == ')')
    return 1;

  return 0;
}

int IsSpace( char c )
{
  if (isspace(c))
    return 1;
  return 0;
}

int _IsPoint( char c )
{
  if (c == '.')
    return 1;
  return 0;
}