#include "../includes/minishell.h"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
void execute(char **tokens, t_data *data)
{
    char *path;
    pid_t pid;

    checkRedirects(tokens, data);
    if (internal_command(tokens, data))
        return;

    char *program = tokens[0];
    char **args = data->path_args;
    path = find_path(program, data);
    if (path == NULL)
    {
        printf("Error\n");
        return;
    }

    // Fork a child process
    pid = fork();

    if (pid == -1)
    {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        // Child process

        setRedirects(data);

        // Replace the last element of args with NULL (required by execve)

        execve(path, args, NULL);
        perror("Execve failed"); // This line will only execute if execve fails
        exit(EXIT_FAILURE);
    }
    else
    {
        // Parent process
        free(path);
        wait(NULL);
    }
}


void checkRedirects(char **tokens, t_data *data)
{
	int i;

	i = 1;
	data->input_redirection = 0;
	data->output_redirection = 0;
	data->input_file = NULL;
	data->output_file = NULL;
    while(i < data->arg_count) {
		if (tokens[i] == NULL)
		{

		}
        else if (ft_strncmp(tokens[i], "<", ft_strlen(tokens[i])) == 0) {
            data->input_redirection = 1;
            data->input_file = tokens[i + 1];
        } else if (ft_strncmp(tokens[i], ">", ft_strlen(tokens[i])) == 0) {
            data->output_redirection = 1;
            data->output_file = tokens[i + 1];
        } else if (ft_strncmp(tokens[i], ">>", ft_strlen(tokens[i])) == 0) {
			data->output_redirection = 1;
			data->append_redirection = 1;
			data->output_file = tokens[i + 1];
		}
		i++;
    }
}

void setRedirects(t_data *data)
{
	int fd_output;
	int	fd_input;
	// If inpus redirection is present, open the file and duplicate file descriptor
    if (data->input_redirection) {
        fd_input = open(data->input_file, O_RDONLY);
        if (fd_input < 0) {
            perror("Failed to open input file");
            exit(EXIT_FAILURE);
        }
        dup2(fd_input, STDIN_FILENO);
        close(fd_input);
    }

    // If output redirection is present, open the file and duplicate file descriptor
    if (data->output_redirection) {
		if (data->append_redirection == 1)
		{
			fd_output = open(data->output_file, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		}
		else
		{
			fd_output = open(data->output_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		}
        if (fd_output < 0) {
            perror("Failed to open output file");
            exit(EXIT_FAILURE);
        }
        dup2(fd_output, STDOUT_FILENO);
        close(fd_output);
    }
	return ;
}

char *find_path(char *program, t_data *data)
{
    char *path_var;
    char *path;
    char *full_path;

    path_var = strdup(data->path_env); // Make a copy of the path_env to avoid modifying the original string
    path = ft_strtok(path_var, ":");
    while (path)
    {
        // Calculate the length needed for the full path
        size_t full_path_len = strlen(path) + 1 + strlen(program) + 1; // path + '/' + program + '\0'
        full_path = malloc(full_path_len);
        if (full_path == NULL)
        {
            perror("Memory allocation error");
            exit(EXIT_FAILURE);
        }

        // Construct the full path
        snprintf(full_path, full_path_len, "%s/%s", path, program);

        // Check if the file exists at the current full path
        if (access(full_path, F_OK) == 0)
        {
            free(path_var);
            return full_path;
        }

        free(full_path);
        path = ft_strtok(NULL, ":");
    }
    free(path_var);
    return NULL;
}