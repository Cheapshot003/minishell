#include "../includes/minishell.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()  
{
  t_data data;
  char *line;
  char **tokens;

  signal(SIGINT, intHandler);
  while (1)
  {
    data.working_dir = getcwd(NULL, 0);
    printf("%s", data.working_dir);
    free(data.working_dir);
    line = readline("$ ");
    if (line[0] == '\0')
    {
      continue;
    }
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

void intHandler(int lol)
{
  (void) lol;
  printf("\n$ ");
  return;
}
