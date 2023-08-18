/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otietz <otietz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 07:21:55 by ohnatiuk          #+#    #+#             */
/*   Updated: 2023/08/18 15:12:02 by otietz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init_variables(unsigned long long	*result, int	*i, int	*sign)
{
	*i = 0;
	*sign = 1;
	*result = 0;
}

long long int	ft_atoi_long(const char *str)
{
	unsigned long long	result;
	int					i;
	int					sign;

	init_variables(&result, &i, &sign);
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == 43)
		i++;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
		if (result > 9223372036854775808u && sign == -1)
			return (-1);
		if (result > 9223372036854775807 && sign == 1)
			return (-1);
	}
	return (result * sign);
}

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
