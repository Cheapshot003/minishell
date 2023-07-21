#include "../includes/minishell.h"
#include <stdio.h>
#include <string.h>

int main()  
{
  char *line;
  char **tokens;
  int i;
  while (1)
  {
    line = readline("$ ");
    i = counttoken(line, ' ');
    i++;
    i--;
    tokens = gettokens(line);
    if (!strcmp(tokens[0], "exit"))
      exit(0);
    execute(tokens);
    wait(NULL);
    free(tokens);
    free(line);
  }
  return 0;
}
