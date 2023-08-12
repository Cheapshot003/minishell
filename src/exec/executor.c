#include "../../includes/minishell.h"


int	execute1(t_data *data, t_exec *exec_head)
{
	t_exec *current_exec;

	current_exec = exec_head;

	while (current_exec && current_exec->path)
	{
		if(fork_exec(data, current_exec) == 1)
		{
			printf("ERROR\n");
		}
		current_exec = current_exec->next;
	}
	return (0);
}

int fork_exec(t_data *data, t_exec *exec)
{
	pid_t pid;
	int	input_fd;
	int output_fd;

	exec->path[0] = expand_path(exec->path[0], data);
	if (exec->path[0] == NULL)
		return (1);
	if (data->builtin == 1)
	{
		data->builtin = 0;
		data->arg_count = getarrlen(exec->path);
		internal_command(exec->path, data);
		return (0);
	}

	char **env_vars = get_env_vars_array(data);
	pid = fork();
	input_fd = 0;
	output_fd = 1;
	if (pid == -1)
	{
		perror("Fork failed\n");
		exit(1);
	}
	else if (pid == 0)
	{
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
		perror("Exec failed\n");
		return (1);
	}
	else
	{
		free(exec->path[0]);
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
char *expand_path(char *path, t_data *data)
{
	if (containsslash(path) == 1)
	{
		return(path);
	}
	if (isbuiltin(path) == 1)
	{
		data->builtin = 1;
		return(path);
	}
	else
	{
		return(find_path(path, data));
	}
}
