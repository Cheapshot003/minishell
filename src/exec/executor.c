#include "../../includes/minishell.h"


int execute1(t_data *data, t_exec *exec_head) {
    t_exec *current_exec = exec_head;
    int input_fd = 0; // Initial input file descriptor
	if (expand_paths(data, exec_head) == 1)
	{
		exiterror(data, "Error: Command not found", 0);
		return (1);
	}
    while (current_exec && current_exec->path) {
        if (pipe(current_exec->pipes) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }

        if (fork_exec(data, current_exec, input_fd, current_exec->pipes[1]) == 1) {
            return (1);
        }

        // Close the write end of the pipe in the parent process
        close(current_exec->pipes[1]);

        // Set the input file descriptor for the next iteration
        input_fd = current_exec->pipes[0];

        current_exec = current_exec->next;
    }

    return 0;
}


int fork_exec(t_data *data, t_exec *exec, int input_fd, int output_fd)
{
	pid_t pid;

	if (data->builtin == 1)
	{
		data->builtin = 0;
		data->arg_count = getarrlen(exec->path);
		internal_command(exec->path, data);
		return (0);
	}

	char **env_vars = get_env_vars_array(data);
	pid = fork();
	signal(SIGQUIT, handleSignalByChild);
	if (pid == -1)
	{
		perror("Fork failed\n");
		exit(1);
	}
	else if (pid == 0)
	{
		if (input_fd != 0) {
            dup2(input_fd, 0);
            close(input_fd); // Close the read end of the previous pipe
        }

        if (exec->next) {
            dup2(output_fd, 1);
        }
		if (exec->input_redirection == 1)
		{
			input_fd = open(exec->input_file, O_RDONLY);
			dup2(input_fd, 0);
			close(input_fd);
		}
		if (exec->output_redirection == 1)
		{
			output_fd = open(exec->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
			dup2(output_fd, 1);
			close(output_fd);
		}
		if (exec->append_redirection == 1)
		{
			output_fd = open(exec->output_file, O_WRONLY | O_CREAT | O_APPEND, 0666);
			dup2(output_fd, 1);
			close(output_fd);
		}
		execve(exec->path[0], exec->path, env_vars);
		handle_execerr(data);
		free(exec->path[0]);
		exec->path[0] = NULL;
		free_env(env_vars);
		return (1);
	}
	else
	{
		free(exec->path[0]);
		exec->path[0] = NULL;
		waitpid(pid, &(data->exit_status), 0);
		data->exit_status = WEXITSTATUS(data->exit_status);
		free_env(env_vars);
	}

	return (0);
}

int	containsslash(char *path)
{
	int i;

	i = 0;
	while (path[i])
	{
		if (path[i] == '\\')
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int isbuiltin(char *path)
{
	if (!ft_strncmp(path, "cd", 3))
	{
		return (1);
	}
	else if (!ft_strncmp(path, "exit", 5))
	{
		return (1);
	}
	else if (!ft_strncmp(path, "pwd", 4))
	{
		return (1);
	}
	else if (!ft_strncmp(path, "echo", 5))
	{
		return (1);
	}
	else if (!ft_strncmp(path, "export", 7))
	{
		return (1);
	}
	else if (!ft_strncmp(path, "unset", 6))
	{
		return (1);
	}
	return (0);
}
int expand_paths(t_data *data, t_exec *exec_head)
{
	t_exec *current;

	current = exec_head;
	while (current && current->path)
	{
		if (containsslash(current->path[0]) == 1)
		{
			return(0);
		}
		if (isbuiltin(current->path[0]) == 1)
		{
			data->builtin = 1;
			return(0);
		}
		else
		{
			current->path[0] = find_path(current->path[0], data);
			if (current->path[0] == NULL)
				return (1);
		}
		current = current->next;
	}
	return(0);
}
