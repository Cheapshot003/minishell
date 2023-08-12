#include "../includes/minishell.h"

 static int received_signal;

void intHandler(int sig, siginfo_t *info, void *context)
{
    (void) sig;
    (void) context;

    received_signal = info->si_code;
    if (info->si_code == 0) {
        // signal in prompt
        printf("\n"); // Move to a new line
        rl_on_new_line(); // Regenerate the prompt on a newline
        rl_replace_line("", 0); // Clear the previous text
        rl_redisplay();
    }
    return;
}

void chldHandler(int sig)
{
    received_signal = 0;
    printf("\n\n");
    (void) sig;
}

void handleSignalByChild(int sig)
{
    (void) sig;

    ft_putstr_fd("Quit (core dumped)\n", 2);
    received_signal = 131;
    signal(SIGQUIT, SIG_IGN);
}

char *getPrompt(char *working_dir)
{
    char *prompt;

    prompt = malloc(strlen(working_dir) + 3);
    prompt[0] = '\0';
    ft_strlcat(prompt, working_dir, strlen(working_dir) + 1);
    ft_strlcat(prompt, "$ ", strlen(working_dir) + 3);
    rl_set_prompt(prompt);
    free(working_dir);
    return (prompt);
}

void free_data(t_data *data)
{
    free(data->full_tokens);
    free(data->path_args);
}

int main(int argc, char **argv, char **envp)
{
  t_data data;
  char *line;
  char *prompt;
  data = *(init_data(&data));

    (void) argc;
    (void) argv;
  struct sigaction sa;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_SIGINFO;
  sa.sa_sigaction = intHandler;
  sigaction(SIGINT, &sa, NULL);
  signal(SIGCHLD,chldHandler);
  data.vars = init_env_vars(envp);
  received_signal = 0;
  using_history();
  while (1)
  {
      if (received_signal != 0)
          continue;
    signal(SIGQUIT, SIG_IGN);
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
		continue;
    if (line && *line)
      add_history(line);
	tokenize(line, &data);
    execute1(&data, data.exec_head);
	free(data.path_args);
    free(line);
  }
  free_data(&data);
  return (0);
}