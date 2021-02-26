/* Date: 30.03.19 */
#include "my_math.h"
#include <string.h>
#include <stdlib.h>

int IsInteger( double x )
{
  if (floor(x) == ceil(x))
    return 1;
  return 0;
}

ANS_T Calculate( char* expression )
{
  TOKEN_T* arr;
  TOKEN_T cur;
  TOKEN_T* r;
  TOKEN_T first, second, res;
  ANS_T answer = {{0}, {1}};
  int a;
  double tg, ctg, arcctg;
  res.type = VALUE;

  arr = Parse(expression);
  r = arr;

  if (arr == NULL)
  {
    answer.is_ans = ERR;
    answer.ans.err = _POINTS;

    free(r);
    return answer;
  }



  a = ConvertToScientific(arr);
  TokenDelSpace(arr);
  TokenDefineMinus(arr);


  STACK_T* stack = CreateStack();

  if (a != 0)
  {
    if (SearchErrors(arr) != RIGHT_EXPRESSION)
    {
      answer.is_ans = ERR;
      answer.ans.err = SearchErrors(arr);

      DeleteStack(&stack);
      free(r);

      return answer;
    }
  } 
  else
  {
    answer.is_ans = ERR;
    answer.ans.err = SCIENCE_FORM;

    DeleteStack(&stack);
    free(r);

    return answer;   
  }

  Transform(arr);

  while (arr->type != DEFAULT)
  {
    cur = *arr;

    if (cur.type == VALUE)
      Push(stack, cur);

    else if (cur.type == FUNCTION)
    {
      first = Pop(stack);

      FUNC functionId = cur.token.function;

      switch(functionId)
      {
        case SQRT:
          if (first.token.value >= 0)
          {
            res.token.value = sqrt(first.token.value);
            Push(stack, res);
          }
          else
          {
            answer.is_ans = ERR;
            answer.ans.err = DEFINITION_AREA;

            DeleteStack(&stack);
            free(r);

            return answer;
          }
          break;

        case SIN:
          res.token.value = sin(first.token.value);
          if (res.token.value > -1e-15 && res.token.value < 1e-15)
            res.token.value = 0;
          Push(stack, res);
          break;
        case ARCSIN:
          if (first.token.value >= -1 && first.token.value <= 1)
          {
            res.token.value = asin(first.token.value);
            Push(stack, res);
            break;
          }
          else
          {
            answer.is_ans = ERR;
            answer.ans.err = DEFINITION_AREA;

            DeleteStack(&stack);
            free(r);

            return answer;
            break;
          }
          break;

        case COS:
          res.token.value = cos(first.token.value);
          if (res.token.value > -1e-15 && res.token.value < 1e-15)
            res.token.value = 0;
          Push(stack, res);
          break;
        case ARCCOS:
          if (first.token.value >= -1 && first.token.value <= 1)
          {
            res.token.value = acos(first.token.value);
            Push(stack, res);
            break;
          }
          else
          {
            answer.is_ans = ERR;
            answer.ans.err = DEFINITION_AREA;

            DeleteStack(&stack);
            free(r);

            return answer;
            break;
          }

        case TG:
          if (cos(first.token.value) > (-6.12323e-17) && cos(first.token.value) < (6.12323e-17))
          {
            answer.is_ans = ERR;
            answer.ans.err = DEFINITION_AREA;

            DeleteStack(&stack);
            free(r);

            return answer;
            break;          
          }

          res.token.value = tan(first.token.value);
          if (res.token.value > -1e-15 && res.token.value < 1e-15)
            res.token.value = 0;
          Push(stack, res);
          break;
        case ARCTG:
          res.token.value = atan(first.token.value);
          Push(stack, res);
          break;

        case CTG:
          tg = tan(first.token.value); 
          if (tg > (-1.22465e-16) && tg < (1.22465e-16))
          {
            answer.is_ans = ERR;
            answer.ans.err = DEFINITION_AREA;

            DeleteStack(&stack);
            free(r);

            return answer;
            break;          
          }
          ctg = 1 / tan(first.token.value);
          res.token.value = ctg;
          if (ctg > -1e-15 && ctg < 1e-15)
            res.token.value = 0;
          Push(stack, res);
          break;
        case ARCCTG:
          ctg = 1 / tan(first.token.value);
          arcctg = PI / 2 - ctg; 
          res.token.value = arcctg;
          Push(stack, res);
          break;

        case FLOOR:
          res.token.value = floor(first.token.value);
          Push(stack, res);
          break;
        case CEIL:
          res.token.value = ceil(first.token.value);
          Push(stack, res);
          break;

        case LN:
          if (first.token.value > 0)
          {
            res.token.value = log(first.token.value);
            Push(stack, res);
            break;
          }
          else
          {
            answer.is_ans = ERR;
            answer.ans.err = DEFINITION_AREA;


            DeleteStack(&stack);
            free(r);


            return answer;
            break;
          }
      }

    }

    else if (cur.type == OPERATOR)
    {
      second.type = DEFAULT;
      second.token.value = 0;
      first = Pop(stack);

      if (!IsEmpty(stack))
        second = Pop(stack);
      res.type = VALUE;
      switch(cur.token.operation.op)
      {
        case '+':
          res.token.value = first.token.value + second.token.value;
          Push(stack, res);
          break;
        case '-':
          if (cur.token.operation.flag == BINARY)
          {
            res.token.value = second.token.value - first.token.value;
            Push(stack, res);
            break;
          }
          else
          {
            res.token.value = (-1) * first.token.value;
            if (second.type != DEFAULT)
              Push(stack, second);
            Push(stack, res);
            break;
          }
        case '*':
          res.token.value = first.token.value * second.token.value;
          Push(stack, res);
          break;
        case '/':
          if (first.token.value != 0)
          {
            res.token.value = second.token.value / first.token.value;
            Push(stack, res);
            break;
          }
          else
          {
            answer.is_ans = ERR;
            answer.ans.err = DIVISION_BY_ZERO;


            DeleteStack(&stack);
            free(r);


            return answer;
            break;
          }

        case '^':
          if (second.token.value < 0 && ceil(first.token.value) != floor(first.token.value))
          {
            answer.is_ans = ERR;
            answer.ans.err = DEFINITION_AREA;


            DeleteStack(&stack);
            free(r);

            return answer;
          }
          res.token.value = pow(second.token.value, first.token.value);
          Push(stack, res);
          break;
      }
    }

    *arr++;
  }


  answer.is_ans = NUM;
  answer.ans.res = Pop(stack).token.value;

  if (!IsEmpty(stack))
  {
    answer.is_ans = ERR;
    answer.ans.err = STACK_NOT_FINISHED;


    DeleteStack(&stack);
    free(r);

    return answer;
  }

  DeleteStack(&stack);
  free(r);

  return answer;
}