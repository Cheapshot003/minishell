#include "../includes/minishell.h"

char **gettokens(char *input)
{
  char **tokens;
  int nToken;
  int i;

  i = 1;
  nToken = counttoken(input, ' ');
  tokens = malloc(sizeof(char *) * nToken + 1);
  tokens[nToken] = NULL;
  if (nToken-- > 0)
    tokens[0] = strtok(input, " ");
  while(nToken-- > 0)
    tokens[i++] = strtok(NULL, " ");
  return tokens;
}

int counttoken(char *str, char delim)
{
  int i = 1;
  while (*str)
  {
    if (*str == delim)
      i++;
    str++;
  }
  return (i);
}
