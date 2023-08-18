/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otietz <otietz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 11:13:21 by otietz            #+#    #+#             */
/*   Updated: 2023/08/18 15:00:20 by otietz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	child_process(t_data *data, t_exec *exec, int input_fd, int output_fd)
{
	int		heredoc_file;
	char	**env_vars;

	if (exec->next)
		dup2(output_fd, 1);
	input_fd = prepare_input_fd_to_exec(exec, input_fd);
	if (input_fd == -1)
		exiterror(data, "File error", 0);
	output_fd = prepare_output_fd_to_exec(exec, output_fd);
	if (output_fd == -1)
		exiterror(data, "File error", 0);
	if (exec->heredoc->delims)
	{
		heredoc_file = open(".temp", O_RDONLY);
		dup2(heredoc_file, 0);
	}
	env_vars = get_env_vars_array(data);
	if (data->skip == 0 && data->exit == 0)
		execve(exec->path[0], exec->path, env_vars);
	handle_execerr(data);
	exit(1);
}

int	fork_exec(t_data *data, t_exec *exec,
		int input_fd, int output_fd)
{
	pid_t	pid;

	if (data->builtin == 1)
	{
		data->builtin = 0;
		data->arg_count = getarrlen(exec->path);
		exec_builtins(data, exec, input_fd, output_fd);
		return (0);
	}
	if (exec->heredoc->numheredoc)
		fill_heredocs(data, exec);
	pid = fork();
	signal(SIGQUIT, handle_signal_by_child);
	if (pid == -1)
		exiterror(data, "Fork failed", 0);
	else if (pid == 0)
		child_process(data, exec, input_fd, output_fd);
	else
	{
		data->wait_pid = pid;
		data->exit_status = WEXITSTATUS(data->exit_status);
	}
	return (0);
}

int	containsslash(char *path)
{
	int	i;

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

int	isbuiltin(char *path)
{
	if (!ft_strncmp(path, "cd", 3))
		return (1);
	else if (!ft_strncmp(path, "exit", 5))
		return (1);
	else if (!ft_strncmp(path, "pwd", 4))
		return (1);
	else if (!ft_strncmp(path, "echo", 5))
		return (1);
	else if (!ft_strncmp(path, "export", 7))
		return (1);
	else if (!ft_strncmp(path, "unset", 6))
		return (1);
	else if (!ft_strncmp(path, "env", 4))
		return (1);
	return (0);
}

int	expand_paths(t_data *data, t_exec *exec_head)
{
	t_exec	*current;
	char	*temp;

	current = exec_head;
	while (current && current->path)
	{
		if (containsslash(current->path[0]) == 1)
			return (0);
		if (isbuiltin(current->path[0]) == 1)
			data->builtin = 1;
		else
		{
			temp = current->path[0];
			current->path[0] = find_path(current->path[0], data);
			free(temp);
			if (current->path[0] == NULL)
				return (1);
		}
		current = current->next;
	}
	return (0);
}
