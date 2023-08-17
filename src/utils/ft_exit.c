/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnatiuk <ohnatiuk@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 07:21:55 by ohnatiuk          #+#    #+#             */
/*   Updated: 2023/08/12 08:29:26 by ohnatiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_with_code(char *code_token, t_data *data)
{
	int	exit_arg;

	if (ft_isnum(code_token) == 0)
	{
		exit_arg = ft_atoi_long(code_token) % 256;
		if (exit_arg != -1)
		{
			rl_clear_history();
			data->exit_arg = exit_arg;
			printf("exit\n");
			return ;
		}
	}
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(code_token, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	data->exit_arg = 2;
}

void	ft_exit(char **tokens, t_data *data)
{
	data->exit = 1;
	if (getarrlen(tokens) > 2)
	{
		printf("exit\n");
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		data->exit_arg = 1;
	}
	else if (tokens[1])
		exit_with_code(tokens[1], data);
	else
		printf("exit\n");
}
