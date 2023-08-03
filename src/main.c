#include "../includes/minishell.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()  
{
  t_data data;
  char *line;
  char **tokens;
  char *prompt;
  signal(SIGINT, intHandler);
  fill_path(&data);
  using_history();
  tokens = NULL;
  while (1)
  {
    data.working_dir = getcwd(NULL, 0);
    prompt = getPrompt(data.working_dir);
	line = readline(prompt);
    free(prompt);
    if (line[0] == '\0')
	{
		//free(tokens);
		//free(line);
		continue;
	}   
    if (line && *line)
      add_history(line);
    tokens = gettokens(line, &data);
    execute(tokens, &data);
    free(tokens);
    free(line);
  }
  return (0);
}

char *getPrompt(char *working_dir)
{
  char *prompt;

  prompt = malloc(strlen(working_dir) + 3);
  prompt[0] = '\0';
  ft_strlcat(prompt, working_dir, strlen(working_dir) + 1);
  ft_strlcat(prompt, "$ ", strlen(working_dir) + 3);
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

void fill_path(t_data *data)
{
  data->path_env = getenv("PATH");
  return ;
}
