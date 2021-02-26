#include "def.h"
#include "string.h"
#include "my_math.h"

int LEN = 30;

/* Main program function.
 * ARGUMENTS:
 *   - arguments count:
 *       int argc;
 *   - arguments:
 *       char *argv[]; 
 * RETURNS:
 *   (int) 0 if success, false otherwise.
 */

int main( int argc, char* argv[] )
{
  _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

  FILE *F = NULL;
  char* s;
  char* cs = NULL;
  int len, i;
  char c = 0, ver;
  ANS_T answer;

  if (argc == 2)
    if (fopen_s(&F, argv[1], "r") == 0)
    {
      
    }
    else
      fprintf(stdout, "ERROR: file could not be opened\n");
  if (argc == 1)
    F = stdin;
  if (argc != 1 && argc != 2)
  {
    fprintf(stdout, "ERROR: too much arguments of command line\n");
    return 0;
  }

  s = malloc(LEN * sizeof(char));
  if (s == NULL)
  {
    fprintf(stdout, "ERROR: memory not allocated\n");
  }



  while (!feof(F))
  {
    ver = (char)fgetc(F);

    i = 1;
    if (ver == EOF)
    {
      free(s);
      fclose(F);
      return 0;
    }


    if (ver != '\n')
    {
      s[0] = ver;

      while ((c = (char)fgetc(F)) != '\n' && (!(feof(F))))
      {
        s[i] = c;
        i++;
        if (i >= LEN)
        {
          s = realloc(s, LEN + 1000);
          if (s == NULL)
            fprintf(stdout, "ERROR: memory not allocated");
          LEN += 1000;
       
        }
      }
      s[i] = 0;
    }

    else
    {
      s[0] = '\n';
      s[1] = 0;
    }

    len = strlen(s);

    cs = malloc((len + 2) * sizeof(char));
    if (cs == NULL)
    {
      fprintf(stdout, "ERROR: memory not allocated\n");
    }

    MyStrcpy(cs, s);
    if (VerifyAlphabet(s) == 0)
      DelSpace(cs);

    if (cs[0] == '/' && cs[1] == '/' || cs[0] == 0)
    {
      fprintf(stdout, "%s", s);
      if (c != EOF && c != 0)
      {
        printf("%c", c);
        c = 0;
      }
      free(cs);
    }
    else
    {
      fprintf(stdout, "%s == ", s);

      if (VerifyValidSymbols(s) != 0 && VerifyPoints(s) != 0 && VerifyE(s) != 0)
      {
        answer = Calculate(s);

        if (answer.is_ans == NUM)
          fprintf (stdout,  "%g", answer.ans.res);
        else
          fprintf (stdout,  "ERROR: ");
      
        switch(answer.ans.err)
        {
          case BRACKETS:
            fprintf (stdout,  "brackets");
            break;
          case DEFINITION_AREA:
            fprintf (stdout, "definition area");
            break;
          case FIRST_OPERATOR:
            fprintf (stdout, "first symbol can't be an operation (except unary minus)");
            break;
          case INCORRECT_NAME:
            fprintf (stdout, "incorrect name of function");
            break;
          case DIVISION_BY_ZERO:
            fprintf (stdout, "division on zero");
            break;
          case UNEXPECTED_FINISH:
            fprintf (stdout, "unexpected finish of expression");
            break;
          case NEED_BRACKETS:
            fprintf (stdout, "you should use brackets or do not use unary operator");
            break;
          case USE_MULTIPLIER:
            fprintf (stdout, "you should use a symbol of multiplier");
            break;
          case TWO_OPERATORS:
            fprintf (stdout, "you can't use two operators in a row");
            break;
          case TWO_VALUES:
            fprintf (stdout, "you can't use two values in a row");
            break;
          case STACK_NOT_FINISHED:
            fprintf (stdout, "stack not finished");
            break;
          case SCIENCE_FORM:
            fprintf (stdout, "science form");
            break;
          case _POINTS:
            fprintf (stdout, "points");
            break;
          case RIGHT_EXPRESSION:
            ;
            break;
        }

      }

      else if (VerifyValidSymbols(s) == 0)
        fprintf(stdout, "ERROR: use English alphabet functions, numbers, spaces and operators only");
      else if (VerifyPoints(s) == 0)
        fprintf(stdout, "ERROR: points"); 
      else if (VerifyE(s) == 0)
        fprintf(stdout, "ERROR: unallowed symbol input");

      else
        ;

      if (c != EOF)
      {
        printf("%c", c);
        c = 0;
      }
      free(cs);
    }
  }

  if (F != stdin)
    fclose(F);

  free(s);


  return 0;
} /* End of 'main' function */