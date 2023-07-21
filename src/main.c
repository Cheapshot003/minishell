#include "../includes/minishell.h"
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()  
{
  t_data data;
  char *line;
  char **tokens;
  int i;
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

void intHandler(int lol)
{
  lol++;
  printf("\n$ ");
  return;
}
