/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otietz <otietz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 19:50:09 by ohnatiuk          #+#    #+#             */
/*   Updated: 2023/08/18 11:17:17 by otietz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pipe_and_fork(t_data *data, t_exec *current_exec, int input_fd)
{
	if (pipe(current_exec->pipes) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	if (fork_exec(data, current_exec,
			input_fd, current_exec->pipes[1]) == 1)
		exiterror(data, "Error", 1);
	close(current_exec->pipes[1]);
}

int	execute1(t_data *data, t_exec *exec_head)
{
	t_exec	*current_exec;
	int		input_fd;

	current_exec = exec_head;
	input_fd = 0;
	if (data->skip)
		return (0);
	if (expand_paths(data, exec_head) == 1)
	{
		exiterror(data, "Error: Command not found", 0);
		return (1);
	}
	while (current_exec && current_exec->path)
	{
		pipe_and_fork(data, current_exec, input_fd);
		input_fd = current_exec->pipes[0];
		current_exec = current_exec->next;
	}
	waitpid(data->wait_pid, &(data->exit_status), 0);
	return (0);
}

int	prepare_input_fd_to_exec(t_exec *exec, int input_fd)
{
	if (input_fd != 0)
	{
		dup2(input_fd, 0);
		close(input_fd);
	}
	if (exec->input_redirection == 1)
	{
		input_fd = open(exec->input_file, O_RDONLY);
		if (input_fd == -1)
			return (-1);
		dup2(input_fd, 0);
		close(input_fd);
	}
	return (input_fd);
}

int	prepare_output_fd_to_exec(t_exec *exec, int output_fd)
{
	if (exec->output_redirection == 1)
	{
		output_fd = open(exec->output_file,
				O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (output_fd == -1)
			return (-1);
		dup2(output_fd, 1);
		close(output_fd);
	}
	if (exec->append_redirection == 1)
	{
		output_fd = open(exec->output_file,
				O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (output_fd == -1)
			return (-1);
		dup2(output_fd, 1);
		close(output_fd);
	}
	return (output_fd);
}
