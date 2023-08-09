#include "../../includes/minishell.h"


int	execute1(t_data *data, t_exec *exec_head)
{
	t_exec *current_exec;

	current_exec = exec_head;

	while (current_exec)
	{
		fork_exec(data, current_exec);
		current_exec = current_exec->next;
	}
	return (0);
}

int fork_exec(t_data *data, t_exec *exec)
{
	pid_t pid;
	int	input_fd;
	int output_fd;

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
		exec->path[0] = find_path(exec->path[0], data);
		execve(exec->path[0], exec->path, NULL);
		perror("Exec failed\n");
		return (1);
	}
	else
	{
		waitpid(pid, &(data->exit_status), 0);
	}

	return (0);
}