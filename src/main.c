#include "../includes/minishell.h"

// static int received_signal;

int main()
{
  t_data data;
  char *line;
  char *prompt;
  data = *(init_data(&data));
  signal(SIGINT, intHandler);
	signal(SIGQUIT, quitHandler);
  data.vars = init_env_vars();
  using_history();
  while (data.exit == 0)
  {
    data.working_dir = getcwd(NULL, 0);
    prompt = getPrompt(data.working_dir);
	line = readline(prompt);
    free(prompt);
		if (line == NULL)
		{
			printf("exit\n");
			break;
		}
    if (line[0] == '\0')
		data.skip = 1;
    if (line && *line)
      add_history(line);
	tokenize(line, &data);
	if(data.skip == 0)
    	execute1(&data, data.exec_head);
	free(data.path_args);
    free(line);
  	free_data(&data);
  	data.skip = 0;
  }
  free_lst(&data);
  return (data.exit_arg);
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
	// received_signal = lol;
	printf("\n"); // Move to a new line
	rl_on_new_line(); // Regenerate the prompt on a newline
	rl_replace_line("", 0); // Clear the previous text
	rl_redisplay();
	return;
}

void quitHandler(int sig)
{
	(void) sig;
}

void fill_path(t_data *data)
{
	data->path_env = getenv("PATH");
	return ;
}

void free_data(t_data *data)
{
	free_t_cmd_list(data->cmd_head);
	free_t_exec_list(data->exec_head);
	if (data->exit_str != NULL)
	{
		free(data->exit_str);
		data->exit_str = NULL;
	}
}