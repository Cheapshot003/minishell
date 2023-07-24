#include "../includes/minishell.h"
#include <readline/history.h>
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
  char *prompt;
  signal(SIGINT, intHandler);
  using_history();
  while (1)
  {
    data.working_dir = getcwd(NULL, 0);
    prompt = getPrompt(data.working_dir);
    line = readline(prompt);
    free(prompt);
    if (line[0] == '\0')
      continue;
    if (line && *line)
      add_history(line);
    tokens = gettokens(line);
    execute(tokens);
    wait(NULL);
    free(tokens);
    free(line);
  }
  return (0);
}

char *getPrompt(char *working_dir)
{
  char *prompt;

  prompt = malloc(strlen(working_dir + 3));
  prompt[0] = '\0';
  strcat(prompt, working_dir);
  strcat(prompt, "$ ");
  free(working_dir);
  return (prompt);
}


void intHandler(int lol)
{
  (void) lol;
  printf("\n"); // Move to a new line
  rl_on_new_line(); // Regenerate the prompt on a newline
  rl_replace_line("", 0); // Clear the previous text
  rl_redisplay();
  return;
}
