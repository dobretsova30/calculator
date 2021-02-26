#pragma once
/* Date: 22.03.19 */
#include <stdlib.h>

#include "token.h"

#define INIT_SIZE 10
#define ADDEND 30

#define STACK_OVERFLOW  -100
#define STACK_UNDERFLOW -101

typedef struct stack_tag 
{
  TOKEN_T* data;
  size_t size;
  size_t top;
} STACK_T;

STACK_T* CreateStack( void );
void DeleteStack( STACK_T** stack );
void ResizeStack( STACK_T* stack );
TOKEN_T Pop( STACK_T* stack );
void Push( STACK_T* stack, TOKEN_T token );
TOKEN_T Peek( const STACK_T* stack );
int IsEmpty( STACK_T* stack );
