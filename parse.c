#include "shell.h"

/*
    parse . particiona o comando Unix (armazenado em ptrLinha) em argumentos
*/

//loop through the input line array storing pointers to the start of each arg in the args, updating a
//counter to return or number of arguments found (essentially words are separated by whitespaces)
//stops as soon as it finds \0
int parse (char *ptrLinha, char **args)
{
  int counter = 0;
  while ('\0' != *ptrLinha)
    {
      /* strip whitespace. Usa um NULL para indicar que o argumento anterior e o ultimo */
      while (isspace ((unsigned char) *ptrLinha))
        *ptrLinha++ = '\0';

      *args++ = ptrLinha;/* salvaguarda argumento */
      counter++;

      while ((*ptrLinha != '\0') && (!isspace ((unsigned char) *ptrLinha)))/* salta sobre o argumento */
        ptrLinha++;
    }
  *args = (char *) NULL;/* o ultimo argumento e NULL */
  return counter;
}
