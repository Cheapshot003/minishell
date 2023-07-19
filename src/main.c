#include "../includes/minishell.h"
#include <stdio.h>
#include <string.h>

int main()  
{
  char *line;
  char **tokens;
  int i;
  i = 0;
  int j = 0;
  while (1)
  {
    j = 0;
    line = readline("$ ");
    i = counttoken(line, ' ');
    tokens = gettokens(line);
    while (j < i)
    {
      printf("%s", tokens[j++]);
    }
    printf("\n");
    if (!strcmp(tokens[0], "exit"))
      exit(0);
    execute(tokens);
    free(tokens);
    free(line);
  }
  return 0;
}
