#include "../includes/minishell.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
void execute(char **tokens, t_data *data)
{
  char *path;

  pid_t pid;
  if (internalCommand(tokens))
    return ;
  char *program = tokens[0];
  char **args = tokens;
  path = find_path(program, data);
  pid = fork();
  if (pid == 0)
    execve(path, args, NULL);
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

char *find_path(char *program, t_data *data)
{
  char *path_var;
  char *path;
  char *full_path;

  path_var = malloc(strlen(data->PATH_ENV + 1));
  path_var[0] = '\0';
  strcpy(path_var, data->PATH_ENV);
  path = strtok(path_var, ":");
  while (path)
  {
    full_path = malloc(strlen(path) + strlen(program) + 2);
    full_path[0] = '\0';
    strcat(full_path, path);
    if (full_path[strlen(path) - 1] != '/')
    {
      full_path[strlen(path)] = '/';
      full_path[strlen(path) + 1] = '\0';
    }
    strcat(full_path, program);
    if (access(full_path, F_OK) == 0)
    {
      free(path_var);
      return (full_path);
    }
    path = strtok(NULL, ":");
  }
  free(path_var);
  return NULL; //TBC
}
