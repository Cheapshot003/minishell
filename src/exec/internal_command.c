/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otietz <otietz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 07:21:55 by ohnatiuk          #+#    #+#             */
/*   Updated: 2023/08/12 08:29:26 by otietz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int internal_command_2(char **tokens, t_data *data)
{
	if (!ft_strncmp(tokens[0], "export", 7))
	{
		data->exit_status = ft_export(data, tokens);
		return (1);
	}
	else if (!ft_strncmp(tokens[0], "unset", 6))
	{
		data->exit_status = ft_unset(data, tokens);
		return (1);
	}
	else if (!ft_strncmp(tokens[0], "env", 4))
	{
		data->exit_status = ft_env(data, tokens);
		return (1);
	}
	return (0);
}

int	internal_command(char **tokens, t_data *data)
{
	if (!ft_strncmp(tokens[0], "cd", 3))
	{
		data->exit_status = ft_cd(tokens, data);
		return (1);
	}
	else if (!ft_strncmp(tokens[0], "exit", 5))
	{
		ft_exit(tokens, data);
	}
	else if (!ft_strncmp(tokens[0], "pwd", 4))
	{
		data->exit_status = ft_pwd();
		return (1);
	}
	else if (!ft_strncmp(tokens[0], "echo", 5))
	{
		data->exit_status = ft_echo(data, tokens);
		return (1);
	}
	return internal_command_2(tokens, data);
}
