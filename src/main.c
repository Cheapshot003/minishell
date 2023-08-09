#include "../includes/minishell.h"

// static int received_signal;

int main()
{
	t_data data;
	char *line;
	char **tokens;
	char **tokens1;
	char *prompt;
	data = *(init_data(&data));
	signal(SIGINT, intHandler);
	signal(SIGQUIT, quitHandler);
	data.vars = NULL;
	using_history();
	tokens = NULL;
	// received_signal = 0;
	while (1)
	{
		data.working_dir = getcwd(NULL, 0);
		prompt = getPrompt(data.working_dir);
		line = readline(prompt);
		free(prompt);
		// line == NULL is ctrl + D
		if (line == NULL)
		{
			printf("exit\n");
			break;
		}
		// handle correctly ctrl + c
		if (line[0] == '\0')
			continue;
		if (line && *line)
			add_history(line);
		tokens = tokenize(line, &data);
		execute(tokens, &data);
		tokens1 = tokens;
		while(*tokens)
		{
			free(*tokens);
			tokens++;
		}
		free(tokens1);
		free(data.path_args);
		free(line);
	}
	free_data(&data);
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
	free(data->full_tokens);
	free(data->path_args);
}