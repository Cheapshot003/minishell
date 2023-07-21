#include "../includes/minishell.h"
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
void execute(char **tokens)
{
  pid_t pid;
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
