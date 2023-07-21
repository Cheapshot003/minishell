#include "../includes/minishell.h"
#include <time.h>
#include <unistd.h>

void execute(char **tokens)
{
  pid_t pid;
  pid = fork();

  char *program = tokens[0];
  char **args = tokens + 1;
  pid = fork();
  if (pid == 0)
    execvp(program, args);
  return ;
}
