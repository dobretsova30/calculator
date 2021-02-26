#pragma once

typedef enum MATHERR
{
  RIGHT_EXPRESSION = 0,

  BRACKETS = 1,
  DEFINITION_AREA = 2,
  INCORRECT_NAME = 3,
  DIVISION_BY_ZERO = 4,
  LANGUAGE = 5,
  UNEXPECTED_FINISH = 6,
  NEED_BRACKETS = 7,
  USE_MULTIPLIER = 8,
  TWO_OPERATORS = 9,
  TWO_VALUES = 10,
  FIRST_OPERATOR = 11,
  STACK_NOT_FINISHED = 12,
  SCIENCE_FORM = 13,
  UNEXPECTED_SYMBOL = 14,
  _POINTS = 15
} MATHERR;

typedef enum IS_ANS
{
  NUM = 1,
  ERR = 0
} IS_ANS;

typedef union ANS
{
  double res;
  MATHERR err;
} ANS;

typedef struct ANS_T
{
  ANS ans;
  IS_ANS is_ans;
} ANS_T;

//int VerifyBrackets( TOKEN_T * s );
