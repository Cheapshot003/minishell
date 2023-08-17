/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otietz <otietz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 19:50:09 by ohnatiuk          #+#    #+#             */
/*   Updated: 2023/08/16 10:45:07 by otietz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_builtins(t_data *data, t_exec *exec, int input_fd, int output_fd)
{
	int	orig_stdin;
	int	orig_stdout;

	orig_stdin = dup(0);
	orig_stdout = dup(1);
	if (input_fd != 0)
	{
		dup2(input_fd, 0);
		close(input_fd);
	}
	if (exec->next)
		dup2(output_fd, 1);
	if (exec->input_redirection == 1)
	{
		input_fd = open(exec->input_file, O_RDONLY);
		if (input_fd == -1)
		{
			perror("Input redirection failed\n");
			return (1);
		}
		dup2(input_fd, 0);
	}
	if (exec->output_redirection == 1)
	{
		output_fd = open(exec->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (output_fd == -1)
		{
			perror("Output redirection failed\n");
			return (1);
		}
		dup2(output_fd, 1);
	}
	if (exec->append_redirection == 1)
	{
		output_fd = open(exec->output_file,
				O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (output_fd == -1)
		{
			perror("Append redirection failed\n");
			return (1);
		}
		dup2(output_fd, 1);
	}
	if (exec->heredoc->numheredoc)
		fill_heredocs(data, exec);
	internal_command(exec->path, data);
	if (input_fd != 0)
		close(input_fd);
	dup2(orig_stdin, 0);
	dup2(orig_stdout, 1);
	return (0);
}
