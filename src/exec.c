#include "../includes/minishell.h"
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
void execute(char **tokens)
{
  pid_t pid;
  if (internalCommand(tokens))
    return ;
  char *program = tokens[0];
  char **args = tokens + 1;
  pid = fork();
  if (pid == 0)
  {
    execvp(program, args);
    exit(0);
  }
  else
  {
    wait(NULL);

  }
  return ;
}

int internalCommand(char **tokens)
{
  if (!strcmp(tokens[0], "cd"))
  {
    chdir(tokens[1]);
    return (1);
  }
  return (0);
}
