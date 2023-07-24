#include "../includes/minishell.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
void execute(char **tokens)
{
  char *path;

  pid_t pid;
  if (internalCommand(tokens))
    return ;
  char *program = tokens[0];
  char **args = tokens;
  path = find_path(program);
  pid = fork();
  if (pid == 0)
  {
    
    execve(program, args, NULL);
    exit(0);
  }
  else
    wait(NULL);
  return ;
}

int internalCommand(char **tokens)
{
  if (!strcmp(tokens[0], "cd"))
  {
    chdir(tokens[1]);
    return (1);
  }
  else if (!strcmp(tokens[0], "exit"))
  {
  free(tokens);
  exit(0);
  }

  return (0);
}

char *find_path(char *program)
{
  char *path_var;
  char *path;

  path_var = getenv("PATH");
  if (path_var == NULL)
    return (NULL);
  return path; //TBC
}
