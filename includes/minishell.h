#ifndef MINISHELL_H

#define MINISHELL_H
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

typedef struct s_data{
  char *working_dir;
  char *PATH_ENV;
} t_data;

int counttoken(char *str, char delim);
char **gettokens(char *input);
void execute(char **tokens, t_data *data);
void intHandler(int lol);
int internalCommand(char **tokens);
char *getPrompt(char *working_dir);
char *find_path(char *program, t_data *data);
void fill_path(t_data *data);
#endif // !MINISHELL_H
