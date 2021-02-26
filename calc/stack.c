#include "stack.h"
#include "def.h"

STACK_T* CreateStack( void )
{
  STACK_T* stack = NULL;
  stack = malloc(sizeof(STACK_T));
  if (stack == NULL)
    exit(MEMORY_ALLOCATION_ERROR);
  stack->size = INIT_SIZE;
  stack->data = calloc(stack->size, sizeof(TOKEN_T));
  if (stack->data == NULL)
  {
    free(stack);
    exit(MEMORY_ALLOCATION_ERROR);
  }
  stack->top = 0;
  return stack;
}

void DeleteStack( STACK_T** stack )
{
  free((*stack)->data);
  free(*stack);
  *stack = NULL;
}

void ResizeStack( STACK_T* stack )
{
  stack->size += ADDEND;
  stack->data = realloc(stack->data, stack->size * sizeof(TOKEN_T));
  if (stack->data == NULL)
    exit(MEMORY_ALLOCATION_ERROR);
}

TOKEN_T Pop( STACK_T* stack )
{
  if (stack->top == 0)
    exit(STACK_UNDERFLOW);
  stack->top--;
  return stack->data[stack->top];
}

void Push( STACK_T* stack, TOKEN_T token )
{
  if (stack->top >= stack->size)
    ResizeStack(stack);
  stack->data[stack->top] = token;
  stack->top++;
}

TOKEN_T Peek( const STACK_T* stack )
{
  if (stack->top <= 0)
    exit(STACK_UNDERFLOW);
  return stack->data[stack->top - 1];
}

int IsEmpty( STACK_T* stack )
{
  if ((stack->top) == 0)
    return 1;
  return 0;
}