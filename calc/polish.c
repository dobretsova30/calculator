/* Date: 23.03.19 */
#include "polish.h"

/* Transforming to polish notation */

void Transform( TOKEN_T* arr )
{
  STACK_T* stack = CreateStack();
  int id;
  int i = 0, j = 0;
  TOKEN_T* out = NULL;
  TOKEN_T current, upper;


  out = calloc(TokenLength(arr) + 1, sizeof(TOKEN_T));
  if (out == NULL)
  {
    /* ALARM */
    exit(MEMORY_ALLOCATION_ERROR);
  }

  while (arr[i].type != DEFAULT)
  {
    current = arr[i];
    id = DefineToken(current);
    switch(id)
    {
      case VALUE:
        out[j++] = current;
        break;

      case LBRACKET:
        Push(stack, current);
        break;

      case RBRACKET:
        while ((upper = Peek(stack)).type != LBRACKET)
        {
          out[j++] = upper;
          Pop(stack);
        }
        Pop(stack); //delete '('
        break;

      case OPERATOR:
        if (IsEmpty(stack))
          Push(stack, current);

        else
        {
          if (current.token.operation.flag == BINARY)
          {
            if (Peek(stack).type != LBRACKET)
            {
              while ((!(IsEmpty(stack)) && (Peek(stack).type != LBRACKET)) && 
                ((current.token.operation.op != '^')?
                (GetPriority(Peek(stack)) <= GetPriority(current)):
                (GetPriority(Peek(stack)) < GetPriority(current))))

                out[j++] = Pop(stack);

              Push(stack, current);
            }
            else
              Push(stack, current);
          }

          else
          {
            if (Peek(stack).type != LBRACKET)
            {
              while ((!(IsEmpty(stack)) && (Peek(stack).type != LBRACKET)) && 
                (GetPriority(Peek(stack)) < GetPriority(current)))

                out[j++] = Pop(stack);

              Push(stack, current);
            }
            else
              Push(stack, current);            
          }
        }   
        break;

      case FUNCTION:
        while ((!(IsEmpty(stack)) && (Peek(stack).type != LBRACKET)) && 
          (GetPriority(Peek(stack)) < GetPriority(current)))

          out[j++] = Pop(stack);

        Push(stack, current);

    } 

    i++;
  }

  while (!IsEmpty(stack))
    out[j++] = Pop(stack);

  out[j++].type = DEFAULT;

  TokenCpy(arr, out);

  DeleteStack(&stack);

  free(out);
}