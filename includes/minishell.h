#ifndef MINISHELL_H

#define MINISHELL_H
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int counttoken(char *str, char delim);
char **gettokens(char *input);
void execute(char **tokens);

#endif // !MINISHELL_H
